#include <common/Common.hpp>
#include <game/ui/ControlGroup.hpp>
#include <game/ui/TypeInfo.hpp>
#include <game/ui/MenuInputManager.hpp>

class Page {
public:

    enum PageID {
        NONE = -1,
        UNK_0,
        ESRB_NOTICE,
        HZ60_SUGGESTION,
        DATA_CORRUPT,
        CANNOT_SAVE,
        SYSTEM_MEMORY_CORRUPT,
        MII_DATA_CORRUPT,
        GP_PAN_OVERLAY,
        VS_PAN_OVERLAY,
        BT_PAN_OVERLAY,
        MR_PAN_OVERLAY,
        COMPETITION_PAN_OVERLAY,
        GP_INTERFACE,
        TT_INTERFACE,
        VS_1P_RACE_INTERFACE,
        VS_2P_RACE_INTERFACE,
        VS_3P_RACE_INTERFACE,
        VS_4P_RACE_INTERFACE,
        BT_1P_INTERFACE,
        BT_2P_INTERFACE,
        BT_3P_INTERFACE,
        BT_4P_INTERFACE,
        COMPETITION_MR_INTERFACE,
        GP_PAUSE_MENU,
        VS_PAUSE_MENU,
        TT_PAUSE_MENU,
        BT_PAUSE_MENU,
        MR_PAUSE_MENU,
        GHOST_RACE_PAUSE_MENU,
        ABANDON_GHOST_RACE,
        QUIT_GHOST_RACE,
        GHOST_REPLAY_PAUSE_MENU,
        GP_END_PROMPT,
        TT_END_PROMPT,
        VS_END_PROMPT,
        BT_END_PROMPT,
        GO_TO_AWARD_PROMPT,
        MR_END_PROMPT,
        COMPETITION_END_PROMPT,
        GHOST_RACE_END_PROMPT,
        GO_TO_FRIEND_ROSTER_PROMPT,
        SEND_GHOST_TO_FRIEND_PROMPT,
        SEND_COMPETITION_RECORD_PROMPT,
        GO_TO_RANKINGS_PROMPT,
        QUIT_CONFIRMATION_PROMPT,
        TT_SPLITS,
        TT_LEADERBOARD,
        GP_VS_SCORE_UPDATE,
        GP_VS_SCORE_OVERALL,
        WIFI_VS_SCORE_UPDATE,
        TEAM_VS_SCORE_OVERALL,
        BT_SCORE_UPDATE,
        BT_SCORE_OVERALL,
        COMPETITION_LEADERBOARD,
        GP_REPLAY_INTERFACE,
        GHOST_RACE_INTERFACE,
        GP_REPLAY_PAUSE_MENU,
        TT_REPLAY_PAUSE_MENU,
        KPAGEID_WIPEPAGE,
        AWARD_INTERFACE,
        CONGRATULATIONS_AWARD,
        CREDITS_PART_1,
        CREDITS_PART_2,
        CONGRATULATIONS_CREDITS,
        WIFI_1P_VS_RACE_INTERFACE,
        WIFI_2P_VS_RACE_INTERFACE,
        WIFI_FROOM_VS_INTERFACE,
        WIFI_FROOM_TEAM_VS_INTERFACE,
        FRIEND_ROOM_SCORE_FINAL,
        DUMMY_45,
        WIFI_VS_END_PROMPT,
        WIFI_VS_QUIT_CONFIRMATION_PROMPT,
        PLEASE_WAIT,
        WIFI_LIVE_VIEW_VS,
        WIFI_LIVE_VIEW_BT,
        START_RACE_PROMPT,
        TEXT_BOX_WITH_SPINNER,
        MESSAGE_POPUP,
        ONLINE_VOTE_PROMPT,
        READING_GHOST_DATA,
        CONNECTING_TO_NINTENDO_WFC,
        FULL_SCREEN_BUTTON_PROMPT,
        TEXT_BOX_WITH_PROMPT,
        POST_PHOTO_TO_WII_MESSAGE_BOARD_PROMPT,
        UNK_54,
        UNK_55,
        LOW_BATTERY_NOTIFICATION,
        TITLE_SCREEN,
        UNK_58,
        DEMO,
        MAIN_MENU,
        UNK_5B,
        MODEL_5C,
        LINE_BACKGROUND_WHITE,
        TOP_MENU_OVERLAY,
        BLINKING_PRESS_A,
        SELECT_MII,
        ACTIVE_CONTROLLER_DISPLAY,
        PLAYER_CONTROLLER_OPT_IN,
        PAIR_CONTROLLER,
        PAIR_CONTROLLER_COMPLETE_PROMPT,
        LICENSE_SELECT,
        MII_CHANGED_PROMPT,
        LICENSE_SETTINGS,
        ERASE_LICENSE_PROMPT,
        SINGLE_PLAYER_MENU,
        GP_CLASS_SELECT,
        CHARACTER_SELECT,
        VEHICLE_SELECT,
        DRIFT_SELECT,
        CUP_SELECT,
        COURSE_SELECT,
        GHOST_SELECT_TOP,
        GHOST_SELECT_LIST,
        VS_MODE_PROMPT,
        VS_RULES,
        TEAM_OVERVIEW,
        BT_MODE_PROMPT,
        VEHICLE_SELECT_BT,
        BT_RULES,
        CUP_SELECT_BT,
        COURSE_SELECT_BT,
        LEVEL_SELECT_MR,
        LEVEL_SELECT_MR_SUBSCREEN,
        MISSION_INFO_PROMPT,
        DRIFT_SELECT_FORCED,
        MISSION_TUTORIAL,
        MODEL_RENDERER,
        MULTI_PLAYER_MENU,
        VEHICLE_SELECT_MULTI_PLAYER,
        DRIFT_SELECT_MULTI_PLAYER,
        TEAM_SELECT_MULTI_PLAYER,
        UNK_84,
        WIFI_FIRST_PLAY,
        ALLOW_DATA_SHARING_PROMPT,
        DISCONNECTED,
        UNK_88,
        WIFI_CONNECTION_ERROR,
        UNK_8A,
        WIFI_MENU,
        WIFI_GAME_MODE_SELECT,
        WIFI_FRIENDS_MENU,
        CHANNEL_FRIENDS_MENU,
        GLOBAL_SEARCH_MANAGER,
        TIMER,
        VR_SCREEN,
        WIFI_VOTING,
        UNK_93,
        UNK_94,
        GLOBE,
        FRIEND_ROSTER,
        NOT_FRIENDS_YET,
        REMOVE_FRIEND_CODE_PROMPT,
        REMOVING_FRIEND_CODE,
        FRIEND_JOIN,
        FRIEND_ROOM_JOIN,
        FRIEND_ROOM_MANAGER,
        FRIEND_ROOM,
        FRIEND_ROOM_MESSAGES,
        UNK_9F,
        UNK_A0,
        UNK_A1,
        CHANNEL,
        RANKINGS,
        CHANNEL_GHOSTS,
        UNK_A5,
        ENTER_FC,
        GHOST_LIST_MANAGER,
        GHOST_HISTOGRAM,
        GHOST_HISTOGRAM_2,
        RANKING_BACK_PAGE,
        TOP_MENU_OVERLAY_AB,
        CHANNEL_CHALLENGE_GHOST_BACKGROUND,
        CHANNEL_CHALLENGE_GHOST,
        RANKING_TOP_TEN,
        RANKING_DETAIL,
        UNK_B0,
        UNK_B1,
        UNK_B2,
        UNK_B3,
        DOWNLOADED_GHOST_LIST,
        ERASE_GHOST_PROMPT,
        UNK_B6,
        UNK_B7,
        UNK_B8,
        UNK_B9,
        COMPETITION_FOR_WII_WHEELS_ONLY,
        UNK_BB,
        UNK_BC,
        UNK_BD,
        UNK_BE,
        UNK_BF,
        OPTIONS,
        WIFI_OPTIONS,
        OPTION_EXPLANATION,
        OPTION_SELECT_2,
        OPTION_SELECT_3,
        RETURN_TO_SYSTEM_MENU_TO_SET_REGION_PROMPT,
        FLAG,
        OPTION_AWAIT,
        OPTION_MESSAGE,
        OPTION_CONFIRM,
        INSTALL_CHANNEL,
        INSTALL_CHANNEL_PROMPT,
        OPTIONS_BACKGROUND,
        UNK_CD,
        RECORDS_OVERALL,
        RECORDS_FAVOURITES,
        RECORDS_FRIENDS,
        RECORDS_WIFI,
        RECORDS_OTHER,
        PAGE_COUNT,
    };

    enum PageState {
        STATE_UNLOADED,
        STATE_LOADING,
        STATE_ACTIVATING,
        STATE_FOCUSED,
        STATE_DEFOCUSING,
        STATE_UNLOADING,
    };

    enum ReplaceAnim {
        ANIM_NONE = -1,
        ANIM_NEXT,
        ANIM_PREV,
    };

    virtual ~Page();
    virtual const char* getPageName();
    virtual int getReplacement();
    virtual int vf_14();
    virtual bool getDiscEnabled();
    virtual void changeSection(int sectionId, int animId, f32 delay);
    virtual void setNextSection(int sectionId, int animId, f32 delay);
    virtual Page* addPage(int pageId, int animId);
    virtual void onInit();
    virtual void onDeinit();
    virtual void onActivate();
    virtual void onDeactivate();
    virtual void beforeInAnim();
    virtual void afterInAnim();
    virtual void beforeOutAnim();
    virtual void afterOutAnim();
    virtual void beforeCalc();
    virtual void afterCalc();
    virtual void calc();
    virtual void onRefocus();
    virtual void onSectionChange();
    virtual void vf_5c();
    virtual TypeInfo* getTypeInfo() const;

    void initChildren(u32 childCount);
    void insertChild(u32 childIdx, UIControl* child, u32 drawPass);

    void playSound(int soundId, int param_3);
    void replace(int animationDirection, float delay);

    void setInputManager(MenuInputManager* manager);

    int pageId;
    int pageState;
    bool canProceed;

    int animId;
    float backTransitionDelay;
    float transitionDelay;

    int activeStateCounter;
    int activeCounter;

    ControlGroup controlGroup;
    MenuInputManager* inputManager;

    int forwardSoundId;
    int backSoundId;
};
size_assert(Page, 0x44);
