#include "world.h"

std::unordered_map<long long, Chunk> world;

void AddObject(int x, int y, Object & obj)
{
    world[coordsToKey(x, y)].objects.push_back(obj);
}

void UpdateWorld(const float & dt)
{

}

void DrawWorld(Transform * camera)
{
    for (int z = floor(camera->position.z / CHUNK_SIZE) - 0; z <= floor(camera->position.z / CHUNK_SIZE) + 0; ++z)
    {
        for (int x = floor(camera->position.x / CHUNK_SIZE) - 0; x <= floor(camera->position.x / CHUNK_SIZE) + 0; ++x)
        {
            long long key = coordsToKey(x, z);
            if (world.find(key) == world.end()) {
                world.emplace(std::piecewise_construct,
                    std::forward_as_tuple(key),
                    std::forward_as_tuple(x, z));
            }
            if (!world[key].generated) {
                world[key].Generate();
            }
            world[key].Draw();

            for (auto & obj : world[key].objects)
            {
                //obj.render(target, content);
            }
        }
    }
}
