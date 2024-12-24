#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>

#include "world.h"

using namespace Ogre;
using namespace OgreBites;

class Game
        : public ApplicationContext
        , public InputListener
{
    private:
        Root* root;
        World world;
    public:
        Game();
        virtual ~Game() {}

        void setup();
        bool keyPressed(const KeyboardEvent& evt);
};