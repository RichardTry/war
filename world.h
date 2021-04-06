#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>

#include "transform.h"
#include "chunk.h"
#include "content.h"

class World
{
    public:
        std::unordered_map<long long, Chunk> world;

        void initWorld();

    public:
        World();
        virtual ~World();

        void addObject(int x, int y, Object & obj);

        void update(const float & dt);
        void render(sf::RenderTarget * target, Content * content, Transform * camera);
};

#endif // WORLD_H
