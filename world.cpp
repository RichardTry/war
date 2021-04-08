#include "world.h"
#include "shader.h"
#include "camera.h"

std::unordered_map<long long, Chunk> world;

sf::Shader world_shader;

void InitWorld()
{
    if (!world_shader.loadFromFile("shaders/world.vert", "shaders/world.frag")) {
        throw std::runtime_error("World shader(s) file(s) not found");
    }
}

void AddObject(int x, int y, Object & obj)
{
    world[coordsToKey(x, y)].objects.push_back(obj);
}

void UpdateWorld(const float & dt)
{
    #warning unused function UpdateWorld
}

void DrawWorld(Transform * camera)
{
    sf::Shader::bind(&world_shader);
    world_shader.setUniform("projection", sf::Glsl::Mat4(glm::value_ptr(projection)));
    world_shader.setUniform("view", sf::Glsl::Mat4(glm::value_ptr(view)));
    for (int z = floor(camera->position.z / CHUNK_SIZE) - 2; z <= floor(camera->position.z / CHUNK_SIZE) + 2; ++z)
    {
        for (int x = floor(camera->position.x / CHUNK_SIZE) - 2; x <= floor(camera->position.x / CHUNK_SIZE) + 2; ++x)
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
            world_shader.setUniform("model", sf::Glsl::Mat4(
                glm::value_ptr(glm::translate(glm::mat4(1.0f), glm::vec3(x * (int)CHUNK_SIZE, 0, z * (int)CHUNK_SIZE)))
            ));
            world[key].Draw();

            for (auto & obj : world[key].objects)
            {
                //obj.render(target, content);
            }
        }
    }
}
