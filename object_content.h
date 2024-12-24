#ifndef OBJECT_CONTENT_H_INCLUDED
#define OBJECT_CONTENT_H_INCLUDED

struct ObjectContent
{
    Ogre::Texture * texture_up;
    Ogre::Texture * texture_down;
    Ogre::Texture * texture_left;
    Ogre::Texture * texture_right;
    Ogre::Vector2f spriteSize;
    Ogre::Vector2f spriteOrigin;
    //Vector2u collision;
    //Vector2u collisionOrigin;
};

#endif // OBJECT_CONTENT_H_INCLUDED

