#include <common/Common.hpp>

class AnmHolder {
public:
    virtual float GetFrameCount();
    virtual float GetFrame() const;
    virtual void SetFrame(float frame);
    virtual void UpdateRateAndSetFrame(float frame);
    virtual float GetUpdateRate() const;
    virtual void SetUpdateRate(float rate);
    virtual bool IsLooped();

    u8 unk[0x1C-0x4];
};
size_assert(AnmHolder, 0x1C);
