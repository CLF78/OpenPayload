#include <common/Common.hpp>
#include <dwc/dwc_base64.h>
#include <dwc/dwc_main.h>
#include <dwc/dwc_match.h>
#include <game/net/RKNetController.hpp>
#include <game/net/RKNetSelectHandler.hpp>
#include <game/net/packet/RKNetRoomPacket.hpp>
#include <game/system/CourseMap.hpp>
#include <game/system/MultiDvdArchive.hpp>
#include <game/system/RaceConfig.hpp>
#include <game/system/RaceManager.hpp>
#include <game/system/ResourceManager.hpp>
#include <nw4r/ut/Lock.hpp>
#include <platform/stdio.h>
#include <platform/string.h>
#include <revolution/es/es.h>
#include <revolutionex/net/NETDigest.h>
#include <wiimmfi/Auth.hpp>
#include <wiimmfi/ConnectionMatrix.hpp>
#include <wiimmfi/Reporting.hpp>
#include <wiimmfi/Status.hpp>
#include <ModSupport.hpp>

namespace Wiimmfi {
namespace Reporting {

u32 sNodeCount;
u32 sTargetFrameCount;

void* GetSubfileHash(const char* path, int src, char* hash) {

    // Get the file and its size
    size_t fileSize;
    void* file = ResourceManager::instance->getFile(src, path, &fileSize);

    // If it doesn't exist, set the hash to zero
    if (!file) {
        hash[0] = '0';
        hash[1] = '\0';

    // Else hash it and print it in the buffer
    } else {
        u32 digest[5];
        NETCalcSHA1(digest, file, fileSize);
        sprintf(hash, HASH_STRING_FMT, digest[0], digest[1], digest[2], digest[3], digest[4]);
    }

    // Return the file pointer anyway
    return file;
}

void ReportAIDPIDMap() {

    // If we are not in a match, bail
    int state = RKNetController::instance->connState;
    if (state != RKNetController::STATE_UNK_5 && state != RKNetController::STATE_MATCHING)
        return;

    // Allocate the buffers and set them to the default base value
    const int BUFFER_SIZE = sizeof("12=4294967295,") * 12 + 1;
    static char sAidPidMap[BUFFER_SIZE] = ",";
    char aidPidMap[BUFFER_SIZE];

    // Insert a single comma if there are no nodes
    if (stpMatchCnt->nodeInfoList.nodeCount == 0)
        strcpy(aidPidMap, ",");

    // Create the data string
    char* mapPtr = aidPidMap;
    for (int i = 0; i < stpMatchCnt->nodeInfoList.nodeCount; i++) {

        // Get the node info, print it and update the offset
        DWCNodeInfo* node = &stpMatchCnt->nodeInfoList.nodeInfos[i];
        int len = sprintf(mapPtr, "%d=%d,", node->aid, node->profileId);
        mapPtr += len;
    }

    // If the data differs, send an update to the server
    if (strcmp(sAidPidMap, aidPidMap))
        Status::SendMessage("slot_pid_matrix", aidPidMap, stpMatchCnt->nodeInfoList.nodeCount);

    // Copy the updated data
    strcpy(sAidPidMap, aidPidMap);
}

void ReportConnectionMatrix(u32 aidsConnectedToMe) {
    Status::SendMessage("connected", "", aidsConnectedToMe);
}

void ReportCommonSubfiles() {

    // Initialize buffer for each message
    char buffers[4][HASH_STRING_SIZE];
    char statusMsgBuffer[200];

    // Send KartParam, DriverParam and ItemSlot hashes
    GetSubfileHash("kartParam.bin", MultiDvdArchive::COMMON, buffers[0]);
    GetSubfileHash("driverParam.bin", MultiDvdArchive::COMMON, buffers[1]);
    GetSubfileHash("ItemSlot.bin", MultiDvdArchive::COMMON, buffers[2]);
    sprintf(statusMsgBuffer, "kart=%s|driver=%s|item=%s", buffers[0], buffers[1], buffers[2]);
    Status::SendMessage("common_subfile_sha1", statusMsgBuffer);

    // Send GeoHit hashes
    GetSubfileHash("GeoHitTableItem.bin", MultiDvdArchive::COMMON, buffers[0]);
    GetSubfileHash("GeoHitTableItemObj.bin", MultiDvdArchive::COMMON, buffers[1]);
    GetSubfileHash("GeoHitTableKart.bin", MultiDvdArchive::COMMON, buffers[2]);
    GetSubfileHash("GeoHitTableKartObj.bin", MultiDvdArchive::COMMON, buffers[3]);
    sprintf(statusMsgBuffer, "ghti=%s|ghtio=%s|ghtk=%s|ghtko=%s", buffers[0], buffers[1],
            buffers[2], buffers[3]);
    Status::SendMessage("common_subfile_sha1", statusMsgBuffer);

    // Send minigame.kmg and ObjFlow hashes
    GetSubfileHash("minigame.kmg", MultiDvdArchive::COMMON, buffers[0]);
    GetSubfileHash("ObjFlow.bin", MultiDvdArchive::COMMON, buffers[1]);
    sprintf(statusMsgBuffer, "minigame=%s|objflow=%s", buffers[0], buffers[1]);
    Status::SendMessage("common_subfile_sha1", statusMsgBuffer);
}

void ReportCourseSubfiles() {

    // Setup hash buffers
    char buffers[3][HASH_STRING_SIZE];
    char statusMsgBuffer[160];

    // Get the KMP and hash it
    MapdataFileAccessor::SData* kmp = (MapdataFileAccessor::SData*)GetSubfileHash("course.kmp",
                                                                                  MultiDvdArchive::COURSE,
                                                                                  buffers[0]);

    // If KMP is invalid bail, the game will crash later anyway
    if (!kmp || kmp->numSections == 0)
        return;

    // Copy the cleaned kmp hash over as a failsafe for missing STGI
    *buffers[1] = *buffers[0];

    // Locate STGI section to overwrite lap/speed modifier
    // Q: Why not just send the values from the KMP instead of hashing it twice??
    for (int i = 0; i < kmp->numSections; i++) {

        // Get KMP section
        KmpSectionHeader* header = (KmpSectionHeader*)((u8*)kmp + kmp->headerSize + kmp->offsets[i]);

        // Check for magic
        if (header->sectionMagic != 'STGI')
            continue;

        // Get section data and check for lap/speed modifications
        // If the data is unchanged, do not hash the KMP again
        MapdataStage::SData* section = (MapdataStage::SData*)(header++);
        if (section->mLapCount == 3 && section->mSpeedMod == 0)
            break;

        // Else reset the fields to the default values and hash the file again
        u8 lapCount = section->mLapCount;
        u16 speedMod = section->mSpeedMod;
        section->mLapCount = 3;
        section->mSpeedMod = 0;
        GetSubfileHash("course.kmp", MultiDvdArchive::COURSE, buffers[1]);

        // Set values back and exit the loop
        section->mLapCount = lapCount;
        section->mSpeedMod = speedMod;
        break;
    }

    // Get KCL hash and send message
    GetSubfileHash("course.kcl", MultiDvdArchive::COURSE, buffers[2]);
    sprintf(statusMsgBuffer, "kmp=%s|clean-kmp=%s|kcl=%s", buffers[0], buffers[1], buffers[2]);
    Status::SendMessage("track_subfile_sha1", statusMsgBuffer);

    // Send LEX file hash, if the file exists
    void* lexFile = GetSubfileHash("course.lex", MultiDvdArchive::COURSE, buffers[0]);
    if (lexFile) {
        sprintf(statusMsgBuffer, "lex=%s", buffers[0]);
        Status::SendMessage("track_subfile_sha1", statusMsgBuffer);
    }

    // Send ItemSlotTable.slt hash, if the file exists
    void* itemSlotFile = GetSubfileHash("ItemSlotTable/ItemSlotTable.slt", MultiDvdArchive::COURSE, buffers[0]);
    if (itemSlotFile) {
        sprintf(statusMsgBuffer, "islot=%s", buffers[0]);
        Status::SendMessage("track_subfile_sha1", statusMsgBuffer);
    }

    // Get course_model hash (or the _d version if it's not available)
    void* courseModelFile = GetSubfileHash("course_model.brres", MultiDvdArchive::COURSE, buffers[0]);
    if (!courseModelFile)
        GetSubfileHash("course_d_model.brres", MultiDvdArchive::COURSE, buffers[0]);

    // Get vrcorn hash (or the _d version if it's not available)
    void* vrcornFile = GetSubfileHash("vrcorn_model.brres", MultiDvdArchive::COURSE, buffers[1]);
    if (!vrcornFile)
        GetSubfileHash("vrcorn_d_model.brres", MultiDvdArchive::COURSE, buffers[1]);

    // Get the minimap model and send message
    GetSubfileHash("map_model.brres", MultiDvdArchive::COURSE, buffers[2]);
    sprintf(statusMsgBuffer, "course%d=%s|vrcorn%d=%s|map=%s", courseModelFile == nullptr,
            buffers[0], vrcornFile == nullptr, buffers[1], buffers[2]);
    Status::SendMessage("track_subfile_sha1", statusMsgBuffer);
}

void ReportFinishTime(u8 playerIdx) {

    // Check if the player is a local player
    bool isLocal = false;
    for (int i = 0; i < RaceConfig::instance->raceScenario.localPlayerCount; i++) {
        if (RaceConfig::instance->raceScenario.settings.hudPlayerIds[i] == playerIdx) {
            isLocal = true;
            break;
        }
    }

    if (!isLocal)
        return;

    // Get the finish time
    char buffer[32];
    u32 timer;
    u32 finishTime = RaceManager::instance->players[playerIdx]->finishTime->getTimeMs();
    snprintf(buffer, sizeof(buffer), "slot=%d|time=%d", playerIdx, finishTime);

    // Get the RaceManager timer
    // Use interrupts to get a more accurate value
    // Q: Is this really necessary?
    {
        nw4r::ut::AutoInterruptLock lock;
        timer = RaceManager::instance->frameCounter;
    }

    // Send message
    Status::SendMessage("finish", buffer, timer);
}

void _ReportFrameCount(u32 frameCount, int profileId) {

    // Only include the PID in the report if the value is not -1
    if (profileId != -1) {
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "%d", profileId);
        Status::SendMessage("frame_count", buffer, frameCount);

    } else
        Status::SendMessage("frame_count", "", frameCount);
}

void ReportFrameCount(u32 frameCount) {

    // NOTE: This function is implemented this way due to the frame counter sometimes being inaccurate
    // Do not send anything if the frame counter hasn't been started
    if (frameCount == 0)
        return;

    // Get the host's PID
    int hostPid = stpMatchCnt->nodeInfoList.nodeInfos[0].profileId;

    // If the target frame is zero this is the first frame, send a message and repeat when countdown ends
    if (sTargetFrameCount == 0) {
        _ReportFrameCount(frameCount, hostPid);
        sTargetFrameCount = 240;
    }

    // The target has been reached, send a message and repeat in 10 seconds
    else if (RaceManager::instance->frameCounter > sTargetFrameCount) {
        _ReportFrameCount(frameCount, (sTargetFrameCount == 240) ? hostPid : -1);
        sTargetFrameCount += 600;
    }
}

void ReportFriendRoomStart(RKNetROOMPacket* packet) {
    if (packet->msgType == RKNetROOMPacket::MSG_ROOM_START)
        Status::SendMessage("friend_event_start", "3", packet->param1);
}

void ReportHostSlotChange() {

    // Get the two AID values to compare
    static u8 sHostAid = -1;
    u8 hostAid = DWC_GetServerAID();

    // If it has changed, report it
    if (sHostAid != hostAid)
        Status::SendMessage("host_slot", "", hostAid);

    // Update the value so this doesn't run again next frame
    sHostAid = hostAid;
}

void ReportMatchStateChange() {

    // Initialize data
    // Q: Why not use the existing debug strings instead of making these?
    static int sMatchState = -1;
    static const char* sMatchStateStrings[DWC_MATCH_STATE_COUNT] = {
        "init",
        "cl_waiting",
        "cl_search_host",
        "cl_wait_resv",
        "cl_nn",
        "cl_gt2",
        "cl_cancel_syn",
        "cl_syn",
        "cl_svdown_1",
        "cl_svdown_2",
        "cl_svdown_3",
        "cl_search_groupid_host",
        "sv_waiting",
        "sv_own_nn",
        "sv_own_gt2",
        "sv_cancel_syn",
        "sv_cancel_syn_wait",
        "sv_syn",
        "sv_syn_wait",
        "wait_close",
        "search_own",
    };

    // If the state has not changed, bail
    int matchState = stpMatchCnt->state;
    if (matchState == sMatchState)
        return;

    // Send message
    Status::SendMessage("dwc_match_state", sMatchStateStrings[matchState], matchState);

    // If we have just become the host, force a suspend update report by setting the node count to 0
    if (sMatchState < DWC_MATCH_STATE_SV_WAITING && matchState >= DWC_MATCH_STATE_SV_WAITING)
        sNodeCount = 0;

    // Update stored state
    sMatchState = matchState;
}

void ReportRaceStage(u32 stage) {

    // Check that the current stage isn't already the new one
    static u32 sCurrStage;
    if (sCurrStage == stage)
        return;

    // Update it and report it otherwise
    sCurrStage = stage;
    Status::SendMessage("race_status", "", stage);
}

void ReportRegionChange() {

    // Use the host profile ID to detect changes
    static u32 sHostPid;

    // If the PID hasn't changed, bail
    u32 hostPid = stpMatchCnt->nodeInfoList.nodeInfos[0].profileId;
    if (hostPid == sHostPid)
        return;

    // Update the stored PID
    sHostPid = hostPid;

    // Report the first four PIDs in the room (????)
    // I seriously think this is pointless and needs to be removed
    char buffer[64];
    DWCNodeInfo* nodeInfos = stpMatchCnt->nodeInfoList.nodeInfos;
    snprintf(buffer, sizeof(buffer), "%d|%d|%d|%d", nodeInfos[0].profileId, nodeInfos[1].profileId,
             nodeInfos[2].profileId, nodeInfos[3].profileId);
    Status::SendMessage("host", buffer, DWC_GetMyAID());

    // Send the current VS and BT region
    char regionData[32];
    snprintf(regionData, sizeof(regionData), "%d|%d", ModSupport::GetVSRegion(), ModSupport::GetBTRegion());
    Status::SendMessage("region", regionData);
}

void ReportSELECTInfo() {

    // Get the outgoing packet
    RKNetSELECTPacket* packet = &RKNetSELECTHandler::instance->sendPacket;

    // Send the packet once we have voted
    // Add a bool to send the report only once
    static bool sPacketSent;
    if (packet->winningVoterAid == 0xFF) {
        sPacketSent = false;
        return;
    }

    if (sPacketSent)
        return;

    // Prepare message
    char buffer[300];
    snprintf(buffer, sizeof(buffer), "driver=%d,%d|vehicle=%d,%d|engine=%d|self=%d|slots=%08x%08x%08x|team=%u",
             packet->playerData[0].character, packet->playerData[1].character,
             packet->playerData[0].vehicle, packet->playerData[1].vehicle,
             packet->engineClass,
             DWC_GetMyAID(),
             packet->playerIdToAid.raw[0], packet->playerIdToAid.raw[1], packet->playerIdToAid.raw[2],
             packet->battleTeamData.raw);

    // Send it
    Status::SendMessage("select", buffer);
    sPacketSent = true;

    // Update connection matrix
    ConnectionMatrix::Update();
}

void ReportServerDown(u32 cmd, u32 pid, u32* data) {

    // If the packet has no extra data, just send the PID
    char buffer[40];
    if (!data)
        snprintf(buffer, sizeof(buffer), "%d", pid);

    // Else send the data both in decimal and hexadecimal form (??)
    else {
        u32 cmdData = NETReadSwappedBytes32(data);
        snprintf(buffer, sizeof(buffer), "%d|%d|%08x", pid, cmdData, cmdData);
    }

    // Send message
    Status::SendMessage("host_debug", buffer, cmd);
}

void ReportSignatureAndCert() {

    ALIGN(32) char cert[IOSECCCertSize];
    ALIGN(32) char signature[IOSECCSigSize];
    ALIGN(32) char b64Signature[DWC_Base64GetEncodedSize(sizeof(signature))+1];
    int tokenLength = Status::sToken ? strlen(Status::sToken) : 0;

    // Get the certificate
    // Removed useless memset call here
    s32 ret = ES_Sign((u8*)Status::sToken, tokenLength, (u8*)signature, (u8*)cert);
    if (ret == ES_ERR_OK) {

        // Encode and send the signature
        int len = DWC_Base64Encode(signature, sizeof(signature), b64Signature, sizeof(b64Signature));
        b64Signature[len] = '\0';
        Status::SendMessage("xy_sg", b64Signature, ret);

        // Encode and send the certificate
        len = DWC_Base64Encode(cert, sizeof(cert), Auth::sConsoleCert, sizeof(Auth::sConsoleCert));
        Auth::sConsoleCert[len] = '\0';
        Status::SendMessage("xy_ct", Auth::sConsoleCert, ret);

    } else {

        // Something failed, send invalid data
        Status::SendMessage("xy_sg", "invalid", ret);
        Status::SendMessage("xy_ct", "invalid", ret);
    }
}

void ReportSuspendUpdate() {

    // Get suspend mask
    static u32 sSuspendMask;
    u32 suspendMask = stpMatchCnt->suspendMatchBitmap;

    // If the suspend mask or the node count haven't been updated, bail
    if (suspendMask == sSuspendMask && sNodeCount == stpMatchCnt->nodeInfoList.nodeCount)
        return;

    // If we are not the host, bail
    if (!DWC_IsServerMyself())
        return;

    // For each aid, set 1 if suspended, 0 if it isn't suspended and the node exists, else "-"
    char buffer[] = "------------";
    for (int i = 0; i < sizeof(buffer) - 1; i++) {
        if (suspendMask & (1 << i))
            buffer[i] = '1';
        else if (DWCi_NodeInfoList_GetNodeInfoForAid(i))
            buffer[i] = '0';
    }

    // Send report and update stored data
    Status::SendMessage("host_suspend_bitmask", buffer);
    sSuspendMask = suspendMask;
    sNodeCount = stpMatchCnt->nodeInfoList.nodeCount;
}

void ReportTrackHash(u32* hash, u8 courseId) {

    // Convert the hash to a string
    // Using sprintf since the output is fixed size and the buffer is big enough
    char buffer[HASH_STRING_SIZE];
    sprintf(buffer, HASH_STRING_FMT, hash[0], hash[1], hash[2], hash[3], hash[4]);

    // Send the hash over with the course id
    Status::SendMessage("track_sha1", buffer, courseId);
}

} // namespace Reporting
} // namespace Wiimmfi
