#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <Ogre.h>
#include "content.h"

class Object
{
    public:
        Ogre::Vector2 position;
        unsigned char rotation;
        std::string contentID;
        Ogre::Entity mesh;

        Object();
        Object(int x, int y, int rot, std::string ID);

        void update(const float & dt, Content * content);
        void render(Ogre::RenderTarget * target, Content * content);
};

#endif // OBJECT_H_INCLUDED

