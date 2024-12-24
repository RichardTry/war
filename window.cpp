#include "window.h"

#include <string>

Ogre::RenderWindow window;
Ogre::Vector2 window_center;

void InitWindow()
{
    std::string title = "War";
    bool fullscreen = false;
    bool vertical_sync_enabled = false;

    // Ogre::RenderSystem context_settings;
    // context_settings.depthBits         = 24; // Request a 24 bits depth buffer
    // context_settings.stencilBits       = 8;  // Request a 8 bits stencil buffer
    // context_settings.antialiasingLevel = 2;  // Request 2 levels of antialiasing

    // (const String& name, unsigned int widthPt, unsigned int heightPt,
    //  bool fullScreen, const NameValuePairList *miscParams)
    window.create(title, 1120, 630, fullscreen, new Ogre::NameValuePairList());
    window.setVSyncEnabled(vertical_sync_enabled);

    window_center = Ogre::Vector2(window.getWidth() / 2, window.getHeight() / 2);
}
