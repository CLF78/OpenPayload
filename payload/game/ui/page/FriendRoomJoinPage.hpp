#include <common/Common.hpp>
#include <game/ui/LayoutUIControl.hpp>
#include <game/ui/MenuInputManager.hpp>
#include <game/ui/Page.hpp>
#include <game/ui/SectionManager.hpp>
#include <game/ui/UIControlTimer.hpp>
#include <game/ui/ctrl/CountdownTimerControl.hpp>

class FriendRoomJoinPage : public Page {
public:

    enum PlayerState {
        NOT_IN_ROOM = -1,
        OPENED_ROOM,
        JOINED_ROOM,
        OPENING_ROOM,
        JOINING_ROOM,
    };

    enum PlayerRoomState {
        ENTERING,
        JOINED_AS_GUEST,
        CONNECTION_ERROR,
        JOINED_AS_HOST,
        STARTING,
        UNK_5,
        UNABLE_TO_JOIN_FRIEND,
        DISCONNECTED_FROM_HOST,
        DISCONNECTED_FROM_OTHER_PLAYERS,
        DISCONNECTED_FROM_OTHER_PLAYERS_2,
        CLOSED,
    };

    virtual ~FriendRoomJoinPage();
    virtual int getReplacement();
    virtual int vf_14();

    virtual void onInit();
    virtual void onActivate();
    virtual void onDeactivate();
    virtual void beforeInAnim();

    virtual void afterCalc();
    virtual void onRefocus();

    virtual TypeInfo* getTypeInfo() const;

    void forceConnectionError() {
        if (playerRoomState == JOINED_AS_GUEST)
            playerRoomState = CONNECTION_ERROR;
    }

    static FriendRoomJoinPage* getPage() {
        return (FriendRoomJoinPage*)SectionManager::instance->curSection->pages[Page::FRIEND_ROOM_JOIN];
    }

    MenuInputManager inputManager;
    LayoutUIControl matchingMessageWindow;
    CountdownTimerControl timerControl;
    UIControlTimer timer;

    int playerState;
    int friendToJoin;
    u8 localPlayerCount;

    int playerRoomState;
    int nextPage;
};
size_assert(FriendRoomJoinPage, 0x364);
