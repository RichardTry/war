#include "world.h"

World::World()
{
    srand(time(0));
    initWorld();
}

World::~World()
{
    //dtor
}

void World::initWorld()
{

}

void World::addObject(int x, int y, Object & obj)
{
    world[coordsToKey(x, y)].objects.push_back(obj);
}

void World::update(const float & dt)
{

}

void World::render(sf::RenderTarget * target, Content * content, Transform * camera)
{
    for (int z = floor(camera->position.z / CHUNK_SIZE) - 0; z <= floor(camera->position.z / CHUNK_SIZE) + 0; ++z)
    {
        for (int x = floor(camera->position.x / CHUNK_SIZE) - 0; x <= floor(camera->position.x / CHUNK_SIZE) + 0; ++x)
        {
            long long key = coordsToKey(x, z);
            auto it = world.find(key);
            if (it == world.end())  world[key] = Chunk(x, z);
            if (!world[key].generated)
                    world[key].generate(world);
            world[key].render(target, content);

            for (auto & obj : world[key].objects)
            {
                //obj.render(target, content);
            }
        }
    }
}
