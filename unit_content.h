#ifndef UNIT_CONTENT_H_INCLUDED
#define UNIT_CONTENT_H_INCLUDED

#include <Ogre.h>

struct UnitContent
{
    Ogre::Vector2f spriteSize;
    Ogre::Vector2f spriteOrigin;
    Ogre::Vector2f collision;
    Ogre::Vector2f collisionOrigin;
    Ogre::Texture texture;
};

#endif // UNIT_CONTENT_H_INCLUDED
