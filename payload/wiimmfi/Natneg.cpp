#include <common/Common.hpp>
#include <dwc/dwc_main.h>
#include <dwc/dwc_match.h>
#include <dwc/dwc_node.h>
#include <dwc/dwc_transport.h>
#include <gs/gt2/gt2Main.h>
#include <gs/gt2/gt2Utility.h>
#include <platform/stdio.h>
#include <platform/string.h>
#include <revolution/os/OS.h>
#include <revolutionex/net/NETDigest.h>
#include <wiimmfi/ConnectionMatrix.hpp>
#include <wiimmfi/Natneg.hpp>

namespace Wiimmfi {
namespace Natneg {

u16 sTimers[12]; // one timer per aid

void ConnectToNode(int nodeIdx) {

    // Get the corresponding node info
    DWCNodeInfo* node = &stpMatchCnt->nodeInfoList.nodeInfos[nodeIdx];
    u8 aid = node->aid;
    int pid = node->profileId;

    // Convert the IP and port to a string
    const char* ipAddr = gt2AddressToString(node->publicip, node->publicport, nullptr);

    // Debug report
    DEBUG_REPORT("[NATNEG-NG] Connecting to node %02d (aid = %d, pid = %d, addr = %s)\n",
                 nodeIdx, aid, pid, ipAddr)

    // Set up the message buffer and write to it
    char buffer[24];
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "%u%s", stpMatchCnt->profileId, "L");

    // Connect to the node
    GT2Connection conn;
    GT2Result ret = gt2Connect(*stpMatchCnt->gt2Socket, &conn, ipAddr, buffer,
                               -1, 2000, stpMatchCnt->gt2Callbacks, 0);

    // If it was successful, store the AID in the custom field
    // Increase value by 1 to leave 0 as sentinel value
    if (ret == GT2_RESULT_SUCCESS)
        conn->aid = aid + 1;
}

void CalcTimers(bool connectedToHost) {

    // Get node count with failsafe
    u32 nodeCount = stpMatchCnt->nodeInfoList.nodeCount;
    if (nodeCount < 1)
        return;

    // Try to connect to each node
    for (int i = 0; i < nodeCount; i++) {

        // Get the aid
        u8 aid = stpMatchCnt->nodeInfoList.nodeInfos[i].aid;

        // If i am host, do not use fast NATNEG
        if (DWC_IsServerMyself()) {
            sTimers[aid] = 0;
            continue;
        }

        // Check for invalid AID
        if (aid > 11)
            continue;

        // If i am connected to the host, set the initial delay to 150
        if (connectedToHost) {
            sTimers[aid] = 150;
            continue;
        }

        // Wait for the timer to reach zero
        if (sTimers[aid] > 0) {
            sTimers[aid]--;
            continue;
        }

        // Skip if we are already connected
        if (DWCi_GetGT2Connection(aid))
            continue;

        // Check for empty PID or my own PID
        u32 pid = stpMatchCnt->nodeInfoList.nodeInfos[i].profileId;
        if (pid == 0 || pid == stpMatchCnt->profileId)
            continue;

        // If we are not in the following forbidden states, try to connect
        u32 matchState = stpMatchCnt->state;
        if (matchState != DWC_MATCH_STATE_CL_WAIT_RESV &&
            matchState != DWC_MATCH_STATE_CL_NN &&
            matchState != DWC_MATCH_STATE_CL_GT2 &&
            matchState != DWC_MATCH_STATE_SV_OWN_NN &&
            matchState != DWC_MATCH_STATE_SV_OWN_GT2)
                ConnectToNode(i);

        // Reset the timer
        sTimers[aid] = 300;
    }
}

void StopMeshMaking() {
    DEBUG_REPORT("[NATNEG-NG] Stopping mesh making\n")
    DWCi_StopMeshMaking();
    DWCi_SetMatchStatus(DWC_IsServerMyself() ? DWC_MATCH_STATE_SV_WAITING : DWC_MATCH_STATE_CL_WAITING);
}

void StoreConnectionAndInfo(int connIdx, GT2Connection conn, DWCNodeInfo* node) {

    // Get the connection pointer and store the new connection to it
    GT2Connection* connPtr = DWCi_GetGT2ConnectionByIdx(connIdx);
    *connPtr = conn;

    // Get the connection info and update it
    DWCConnectionInfo* connInfo = DWCi_GetConnectionInfoByIdx(connIdx);
    connInfo->index = connIdx;
    connInfo->aid = node->aid;
    connInfo->profileId = node->profileId;
    conn->data = connInfo;
    DEBUG_REPORT("[NATNEG-NG] Stored connection with PID %d\n", node->profileId)

    // Reset data receive time and update connection matrix
    DWCi_ResetLastSomeDataRecvTimeByAid(node->aid);
    ConnectionMatrix::Update();
}

void ConnectAttemptCallback(GT2Socket socket, GT2Connection conn, u32 ip, u16 port, int latency,
                            const char* msg, int msgLen) {

    // Obtain the PID from the message
    char* msgBuffer;
    u32 pid = strtoul(msg, &msgBuffer, 10);

    // If the message was not generated from our ConnectToNode function, fall back to original game behaviour
    if (*msgBuffer != 'L') {
        DWCi_GT2ConnectAttemptCallback(socket, conn, ip, port, latency, msg, msgLen);
        return;
    }

    // If no match control structure is present, bail
    if (!stpMatchCnt)
        return;

    // If we are still in INIT state, reject the connection attempt
    if (stpMatchCnt->state == DWC_MATCH_STATE_INIT) {
        DEBUG_REPORT("[NATNEG-NG] Connection rejected from PID %d (INIT state)\n", pid)
        gt2Reject(conn, "wait1", -1);
        return;
    }

    // If the PID is not found, reject the connection attempt
    DWCNodeInfo* node = DWCi_NodeInfoList_GetNodeInfoForProfileId(pid);
    if (!node) {
        DEBUG_REPORT("[NATNEG-NG] Connection rejected from PID %d (PID not found)\n", pid)
        gt2Reject(conn, "wait2", -1);
        return;
    }

    // If the connection already exists, bail
    if (DWCi_GetGT2Connection(node->aid)) {
        DEBUG_REPORT("[NATNEG-NG] Connection already exists with PID %d\n", pid)
        return;
    }

    // Stop mesh making if we are stuck doing NATNEG
    switch(stpMatchCnt->state) {

        // Waiting for reservation response
        // Running NATNEG (both server and client)
        // Establishing GT2 connection (server only)
        case DWC_MATCH_STATE_CL_WAIT_RESV:
        case DWC_MATCH_STATE_CL_NN:
        case DWC_MATCH_STATE_SV_OWN_NN:
        case DWC_MATCH_STATE_SV_OWN_GT2:
            if (pid == stpMatchCnt->tempNewNodeInfo.profileId)
                StopMeshMaking();
            break;

        // Establishing GT2 connection (client only)
        case DWC_MATCH_STATE_CL_GT2:
            if (pid == stpMatchCnt->tempNewNodeInfo.profileId) {
                DWCi_GT2ConnectAttemptCallback(socket, conn, ip, port, latency, msg, msgLen);
                return;
            }
            break;

        // Do nothing in all other cases
        default:
            break;
    }

    // If the server is full, bail
    int connIdx = DWCi_GT2GetConnectionListIdx();
    if (connIdx == -1) {
        DEBUG_REPORT("[NATNEG-NG] Connection failed with PID %d (server full)\n", pid)
        return;
    }

    // Store IP and port
    node->gt2Ip = ip;
    node->gt2Port = port;

    // Accept the connection, if it fails bail
    // The game normally refuses to do this if it's not in the DWC_MATCH_STATE_CL_NN or
    // DWC_MATCH_STATE_CL_GT2 state
    if (!gt2Accept(conn, stpMatchCnt->gt2Callbacks)) {
        DEBUG_REPORT("[NATNEG-NG] Connection failed with PID %d (gt2Accept failed)\n", pid)
        return;
    }

    // Store the connection and its info
    StoreConnectionAndInfo(connIdx, conn, node);
}

void ConnectedCallback(GT2Connection conn, GT2Result result, const char* msg, int msgLen) {

    // Check if the custom aid field was set, if not fall back to original game behaviour
    if (conn->aid == 0) {
        DWCi_GT2ConnectedCallback(conn, result, msg, msgLen);
        return;
    }

    // Get the actual aid
    u8 aid = conn->aid - 1;

    // If the connection attempt resulted into a NATNEG error try again in 150 frames
    // Only do so on one side of the connection by comparing the PIDs
    if (result == GT2_RESULT_NEGOTIATION_ERROR) {
        DEBUG_REPORT("[NATNEG-NG] Negotiation error with AID %d\n", aid)
        DWCNodeInfo* node = DWCi_NodeInfoList_GetNodeInfoForAid(aid);
        if (node && node->profileId <= stpMatchCnt->profileId)
            sTimers[aid] = 150;
        return;
    }

    // For all other results than GT2_RESULT_SUCCESS, reset the timer if a wait message was received
    if (result != GT2_RESULT_SUCCESS) {

        if (msg && (!strcmp(msg, "wait1") || !strcmp(msg, "wait2"))) {
            DEBUG_REPORT("[NATNEG-NG] Received wait message %s from AID %d\n", msg, aid)
            sTimers[aid] = 0;
        }

        return;
    }

    // If we are still in INIT state, bail
    if (stpMatchCnt->state == DWC_MATCH_STATE_INIT) {
        DEBUG_REPORT("[NATNEG-NG] Ignoring connection from AID %d (INIT state)\n", aid)
        return;
    }

    // If the AID is not found, reject the connection attempt
    DWCNodeInfo* node = DWCi_NodeInfoList_GetNodeInfoForAid(aid);
    if (!node) {
        DEBUG_REPORT("[NATNEG-NG] Ignoring connection from AID %d (invalid AID)\n", aid)
        return;
    }

    // If the connection already exists, bail
    if (DWCi_GetGT2Connection(node->aid)) {
        DEBUG_REPORT("[NATNEG-NG] Connection already exists with AID %d\n", node->aid)
        return;
    }

    // Stop mesh making if we are stuck doing NATNEG
    switch(stpMatchCnt->state) {

        // Waiting for reservation response
        // Running NATNEG (both server and client)
        // Establishing GT2 connection (server only)
        case DWC_MATCH_STATE_CL_WAIT_RESV:
        case DWC_MATCH_STATE_CL_NN:
        case DWC_MATCH_STATE_SV_OWN_NN:
        case DWC_MATCH_STATE_SV_OWN_GT2:
            if (node->profileId == stpMatchCnt->tempNewNodeInfo.profileId)
                StopMeshMaking();
            break;

        // Establishing GT2 connection (client only)
        case DWC_MATCH_STATE_CL_GT2:
            if (node->profileId == stpMatchCnt->tempNewNodeInfo.profileId) {
                DWCi_GT2ConnectedCallback(conn, result, msg, msgLen);
                return;
            }
            break;

        // Do nothing in all other cases
        default:
            break;
    }

    // If the server is full, bail (the game will close all connections in this case, so we avoid it)
    int connIdx = DWCi_GT2GetConnectionListIdx();
    if (connIdx == -1) {
        DEBUG_REPORT("[NATNEG-NG] Connection failed with AID %d (server full)\n", node->aid)
        return;
    }

    // Store IP, port and connection
    node->gt2Ip = conn->ip;
    node->gt2Port = conn->port;
    StoreConnectionAndInfo(connIdx, conn, node);
}

DWCNodeInfo* GetNextMeshMakingNode() {

    // Initialize variables
    s64 minNextTryTime = (1 << 63) - 1;
    DWCNodeInfo* minNextTryTimeNode = nullptr;

    // Get each node
    for (int i = 0; i < stpMatchCnt->nodeInfoList.nodeCount; i++) {
        DWCNodeInfo* node = &stpMatchCnt->nodeInfoList.nodeInfos[i];

        // Skip my own node
        if (node->profileId == stpMatchCnt->profileId)
            continue;

        // Skip nodes we are already connected to
        if (DWCi_GetGT2Connection(node->aid))
            continue;

        // If the retry time is empty, fill it
        if (node->nextMeshMakeTryTick == 0)
            node->nextMeshMakeTryTick = DWCi_GetNextMeshMakeTryTick();

        // Check that the time is less than the current minimum time
        // If so, select this node as the one to potentially do NATNEG with
        if (node->nextMeshMakeTryTick < minNextTryTime) {
            minNextTryTime = node->nextMeshMakeTryTick;
            minNextTryTimeNode = node;
        }
    }

    // Check if the minimum time has been reached
    if (OSGetTime() <= minNextTryTime)
        return nullptr;

    // All checks passed, return the node we have found (if any)
    DEBUG_REPORT("[NATNEG-NG] Got next connect node %d\n", minNextTryTimeNode)
    return minNextTryTimeNode;
}

bool PreventRepeatNATNEGFail(u32 failedPid) {

    // Define an array to store the PIDs who have already failed NATNEG
    static u32 sFailedPids[10], sFailedPidsIdx;

    // Only run the check for the host
    if (!DWC_IsServerMyself())
        return false;

    // Check if the PID is valid, if not don't count the attempt
    if (failedPid == 0)
        return false;

    // If the PID is already in the list, do not count the failed attempt
    for (int i = 0; i < ARRAY_SIZE(sFailedPids); i++) {
        if (sFailedPids[i] == failedPid) {
            DEBUG_REPORT("Detected repeated NATNEG fail with PID %d\n", failedPid)
            return false;
        }
    }

    // Store the PID in the list through a rolling counter and count the attempt
    if (sFailedPidsIdx == ARRAY_SIZE(sFailedPids)) { sFailedPidsIdx = 0; }
    sFailedPids[sFailedPidsIdx++] = failedPid;
    return true;
}

void RecoverSynAckTimeout() {

    // Use an internal timer to determine the frequency of the check
    static u32 sSynAckTimer;

    // If we're not the host or we're not in SYN state, bail
    if (stpMatchCnt->state != DWC_MATCH_STATE_SV_SYN) {
        sSynAckTimer = 0;
        return;
    }

    // Update the timer and run the code every 150 frames
    if (++sSynAckTimer % 150)
        return;

    // If no nodes are connected, bail
    u32 nodeCount = stpMatchCnt->nodeInfoList.nodeCount;
    if (nodeCount == 0)
        return;

    // Get the connected AIDs, insert the newly connected one
    // Remove the AIDs who have completed SYN-ACK and my own
    u32 noSynAckAids = DWC_GetAIDBitmap();
    noSynAckAids |= (1 << stpMatchCnt->tempNewNodeInfo.aid);
    noSynAckAids ^= stpMatchCnt->synAckBit;
    noSynAckAids &= ~(1 << DWC_GetMyAID());
    DEBUG_REPORT("[NATNEG-NG] SYN-ACK not completed with AIDs %08X\n", noSynAckAids)

    // Send a NEW_PID_AID command to every AID left in the map
    // Only do so once
    if (sSynAckTimer == 150) {

        // Prepare the data
        DWCMatchCommandNewPidAid cmd;
        NETWriteSwappedBytes32(&cmd.pid, stpMatchCnt->tempNewNodeInfo.profileId);
        NETWriteSwappedBytes32(&cmd.aid, stpMatchCnt->tempNewNodeInfo.aid);

        // Send it
        for (int i = 0; i < nodeCount; i++) {
            if (noSynAckAids >> i & 1) {
                DWCNodeInfo* node = &stpMatchCnt->nodeInfoList.nodeInfos[i];
                DWCi_SendMatchCommand(DWC_MATCH_CMD_NEW_PID_AID, node->profileId, node->publicip,
                                      node->publicport, &cmd, DWC_MATCH_CMD_GET_SIZE(sizeof(cmd)));
            }
        }
    }

    // Send a SYN command periodically, but save the last send time first
    s64 lastSendTime = stpMatchCnt->lastSynSent;
    for (int i = 0; i < nodeCount; i++) {
        if (noSynAckAids >> i & 1)
            DWCi_SendMatchSynPacket(i, DWC_MATCH_SYN_CMD_SYN);
    }

    // Restore the SYN send time
    stpMatchCnt->lastSynSent = lastSendTime;
}

void StopNATNEGAfterTime() {

    // If at least 11 seconds haven't passed since the last state change, bail
    if (OSTicksToSeconds(OSGetTime() - sMatchStateTick) <= 11)
        return;

    // If we are the host, bail
    if (DWC_IsServerMyself())
        return;

    // If we are not in a NATNEG state, bail
    int state = stpMatchCnt->state;
    if (state != DWC_MATCH_STATE_CL_WAIT_RESV &&
        state != DWC_MATCH_STATE_CL_NN &&
        state != DWC_MATCH_STATE_CL_GT2)
            return;

    // Stop NATNEG and change state if necessary
    BOOL ret = DWCi_StopMeshMaking();
    DEBUG_REPORT("[NATNEG-NG] Stopped mesh making with result %d\n", ret)
    if (ret)
        DWCi_SetMatchStatus(DWC_MATCH_STATE_CL_WAITING);
}

} // namespace Natneg
} // namespace Wiimmfi
