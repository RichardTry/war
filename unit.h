#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED

#include "unit_content.h"

class Unit
{
    private:

        Ogre::Vector2f position;
        unsigned int contentID;
        unsigned int direction;

    public:

        void update(const float & dt, std::vector<UnitContent> & unitlib);
        void render(Ogre::RenderTarget * target, std::vector<UnitContent> & unitlib);
};

#endif // UNIT_H_INCLUDED
