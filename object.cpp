#include "object.h"

Object::Object()
{

}

Object::Object(int x, int y, int rot, std::string ID)
{
    position = Ogre::Vector2(x, y);
    rotation = rot;
    contentID = ID;
}

void Object::update(const float & dt, Content * content)
{

}

void Object::render(Ogre::RenderTarget * target, Content * content)
{
    //mesh.Draw();
}

