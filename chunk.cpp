#include "chunk.h"
#include "world.h"
#include <iostream>

Chunk::~Chunk()
{

}

Chunk::Chunk()
{
    //std::cout << "Constructor 1" << std::endl;
    generated = false;
}

Chunk::Chunk(int x, int y)
{
    //std::cout << "Constructor 2" << std::endl;
    position.x = x;
    position.y = y;
    perlinVector.x = rand() % (CHUNK_FACTOR + 1) - CHUNK_FACTOR / 2;
    perlinVector.y = rand() % (CHUNK_FACTOR + 1) - CHUNK_FACTOR / 2;
    generated = false;
}

long long coordsToKey(int x, int y)
{
    return (((long long)x) << 32) + (long long)y;
}

void Chunk::Draw()
{

    mesh.Draw();
}

void Chunk::Generate()
{
    long long keyRight = coordsToKey(position.x + 1, position.y);
    long long keyBottom = coordsToKey(position.x, position.y + 1);
    long long keyBottomRight = coordsToKey(position.x + 1, position.y + 1);

    sf::Vector2i perlinVectorRight, perlinVectorBottom, perlinVectorBottomRight;

    if (world.find(keyRight) != world.end())
        perlinVectorRight = world[keyRight].perlinVector;
    else
    {
        world.emplace(std::piecewise_construct,
            std::forward_as_tuple(keyRight),
            std::forward_as_tuple(position.x + 1, position.y));
        perlinVectorRight = world[keyRight].perlinVector;
    }

    if (world.find(keyBottom) != world.end())
        perlinVectorBottom = world[keyBottom].perlinVector;
    else
    {
        world.emplace(std::piecewise_construct,
            std::forward_as_tuple(keyBottom),
            std::forward_as_tuple(position.x, position.y + 1));
        perlinVectorBottom = world[keyBottom].perlinVector;
    }

    if (world.find(keyBottomRight) != world.end())
        perlinVectorBottomRight = world[keyBottomRight].perlinVector;
    else
    {
        world.emplace(std::piecewise_construct,
            std::forward_as_tuple(keyBottomRight),
            std::forward_as_tuple(position.x + 1, position.y + 1));
        perlinVectorBottomRight = world[keyBottomRight].perlinVector;
    }

    for (uint y = 0; y < CHUNK_SIZE; ++y)
        for (uint x = 0; x < CHUNK_SIZE; ++x)
        {
            int termLeftTop, termLeftBot, termRightBot, termRightTop;
            termLeftTop = perlinVector.x * x + perlinVector.y * y;
            termLeftBot = perlinVectorBottom.x * x + perlinVectorBottom.y * (y - CHUNK_SIZE + 1);
            termRightBot = perlinVectorBottomRight.x * (x - CHUNK_SIZE + 1) + perlinVectorBottomRight.y * (y - CHUNK_SIZE + 1);
            termRightTop = perlinVectorRight.x * (x - CHUNK_SIZE + 1) + perlinVectorRight.y * y;

            float tx = float(x) / (CHUNK_SIZE - 1);
            float ty = float(y) / (CHUNK_SIZE - 1);
            int xTop = termLeftTop + tx * (termRightTop - termLeftTop);
            int xBot = termLeftBot + tx * (termRightBot - termLeftBot);
            int res = xTop + ty * (xBot - xTop);
            res = std::min(std::max(0, res / 2), 8);
            height[x][y] = res;
            if (res == 0) tiles[x][y].type = "water";
            if (res == 1)
            {
                tiles[x][y].type = "sand";
                if (rand() % 20 == 0) objects.push_back(Object(position.x * CHUNK_SIZE + x, position.y * CHUNK_SIZE + y, 0, "palm1"));
            }
            if (res == 2) tiles[x][y].type = "wet_grass";
            if (res == 3) tiles[x][y].type = "dry_grass";
            if (res == 4) tiles[x][y].type = "sand";
            if (res == 5) tiles[x][y].type = "grass";
            if (res == 6)
            {
                tiles[x][y].type = "cold_grass";
                if (rand() % 5 == 0) objects.push_back(Object(position.x * CHUNK_SIZE + x, position.y * CHUNK_SIZE + y, 0, "tree1"));
            }
            if (res == 7) tiles[x][y].type = "ice_grass";
            if (res == 8) tiles[x][y].type = "snow";
        }
    generated = true;
    Recalculate();
}

void Chunk::Recalculate()
{
    mesh.Clear();

    std::vector<glm::vec3> vertexes;
    std::vector<glm::vec3> colors;
    unsigned int x;
    for (x = 0; x < CHUNK_SIZE; ++x) {
        unsigned int z;
        for (z = 0; z <= CHUNK_SIZE; ++z) {
            vertexes.push_back({x, height[x][z] - 0.1, z}); colors.push_back({height[x][z], 0, 1.0-(float)height[x][z]/6});
        }
        for (z = 0; z < CHUNK_SIZE; ++z) {
            vertexes.push_back({x + 0.5, height[x][z], z + 0.5}); colors.push_back({height[x][z], 0.5, 1.0-(float)height[x][z]/6});
        }
    }
    for (unsigned int z = 0; z <= CHUNK_SIZE; ++z) {
        vertexes.push_back({x, height[x][z], z}); colors.push_back({1.0, 1.0, 1});
    }
    mesh.AddVBO(vertexes);
    mesh.AddVBO(colors);

    std::vector<unsigned> indices;
    for (unsigned int x = 0; x < CHUNK_SIZE; ++x){
        for (unsigned int z = 0; z < CHUNK_SIZE; ++z){
            unsigned i[5] = {x * (CHUNK_SIZE * 2 + 1) + z, x * (CHUNK_SIZE * 2 + 1) + z + 1, x * (CHUNK_SIZE * 2 + 1) + z + CHUNK_SIZE + 1, (x + 1) * (CHUNK_SIZE * 2 + 1) + z, (x + 1) * (CHUNK_SIZE * 2 + 1) + z + 1};
            indices.push_back(i[0]); indices.push_back(i[2]); indices.push_back(i[1]);
            indices.push_back(i[1]); indices.push_back(i[2]); indices.push_back(i[4]);
            indices.push_back(i[4]); indices.push_back(i[2]); indices.push_back(i[3]);
            indices.push_back(i[3]); indices.push_back(i[2]); indices.push_back(i[0]);
        }
    }
    mesh.AddEBO(indices);
}
