#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm/glm.hpp"


class Transform
{
    public:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        Transform();
        virtual ~Transform();
};

#endif // TRANSFORM_H
