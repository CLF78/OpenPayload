#include <common/Common.hpp>

namespace EGG {
    
class ColorFader;
class Scene;

class SceneManager {
public:
    void* vtable;
    void* creator;
    u32 _8;

    Scene* currentScene;
    SceneManager* parent;
    int nextSceneId;
    int _18, _1C;

    int transitionStatus;
    ColorFader* currentFader;
    u32 useMem2;
};
size_assert(SceneManager, 0x2C);

} // namespace EGG
