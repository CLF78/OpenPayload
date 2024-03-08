#include <common/Common.hpp>

class UIAnimationGroup {
public:
    void setAnimation(u32 animationId, float frame);
};

class UIAnimator {
public:
    UIAnimationGroup* getGroup(u32 groupId);

    u8 _0[0x10];
};
size_assert(UIAnimator, 0x10);
