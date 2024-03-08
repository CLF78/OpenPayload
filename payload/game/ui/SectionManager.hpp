#include <common/Common.hpp>
#include <game/system/SaveGhostManager.hpp>
#include <game/ui/GlobalContext.hpp>
#include <game/ui/MessageGroup.hpp>
#include <game/ui/Section.hpp>

class SectionManager {
public:
    Section* curSection;
    u8 unk[0x8C];

    SaveGhostManager* saveGhostManager;
    MessageGroup* systemMsgGroup;
    GlobalContext* globalContext;

    static SectionManager* instance;
};
size_assert(SectionManager, 0x9C);
