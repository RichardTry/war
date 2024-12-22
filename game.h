#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>

using namespace Ogre;
using namespace OgreBites;

class Game
        : public ApplicationContext
        , public InputListener
{
private:
    SceneManager* scnMgr;

public:
    Game();
    virtual ~Game() {}

    Camera* createCamera(const String& name, const float& near_clip_distance, const bool& auto_aspect_ratio)
    void addOgreHead(const Vector3& position, const Vector3& scale, const Radian& rotation_angle);
    void setup();
    bool keyPressed(const KeyboardEvent& evt);
};