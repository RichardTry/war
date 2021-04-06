#include "chunk.h"
#include <iostream>

Chunk::Chunk()
{
    generated = false;
}

Chunk::Chunk(int x, int y)
{
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

void Chunk::render(sf::RenderTarget * target, Content * content)
{
    mesh.Draw();
}

void Chunk::generate(std::unordered_map<long long, Chunk> & world)
{
    long long keyRight = coordsToKey(position.x + 1, position.y);
    long long keyBottom = coordsToKey(position.x, position.y + 1);
    long long keyBottomRight = coordsToKey(position.x + 1, position.y + 1);

    sf::Vector2i perlinVectorRight, perlinVectorBottom, perlinVectorBottomRight;

    auto it = world.find(keyRight);
    if (it != world.end())
        perlinVectorRight = (it->second.perlinVector);
    else
    {
        world[keyRight] = Chunk(position.x + 1, position.y);
        perlinVectorRight = world[keyRight].perlinVector;
    }

    it = world.find(keyBottom);
    if (it != world.end())
        perlinVectorBottom = (it->second.perlinVector);
    else
    {
        world[keyBottom] = Chunk(position.x, position.y + 1);
        perlinVectorBottom = world[keyBottom].perlinVector;
    }

    it = world.find(keyBottomRight);
    if (it != world.end())
        perlinVectorBottomRight = (it->second.perlinVector);
    else
    {
        world[keyBottomRight] = Chunk(position.x + 1, position.y + 1);
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
    recalculate();
}

void Chunk::recalculate()
{
    mesh.Clear();

    std::vector<glm::vec3> vertexes;
    std::vector<glm::vec3> colors;
    int x;
    for (x = 0; x < CHUNK_SIZE; ++x) {
        int z;
        for (z = 0; z <= CHUNK_SIZE; ++z) {
            vertexes.push_back({x, height[x][z] - 0.1, z}); colors.push_back({0, rand()%50 / 100.0 + 0.3, 0});
        }
        for (z = 0; z < CHUNK_SIZE; ++z) {
            vertexes.push_back({x + 0.5, height[x][z], z + 0.5}); colors.push_back({0.5, rand()%50 / 100.0 + 0.5, 0});
        }
    }
    for (int z = 0; z <= CHUNK_SIZE; ++z) {
        vertexes.push_back({x, height[x][z], z}); colors.push_back({0, rand()%50 / 100.0 + 0.1, 1});
    }
    mesh.AddVBO(vertexes);
    mesh.AddVBO(colors);

    std::vector<unsigned> indices;
    for (int x = 0; x < CHUNK_SIZE; ++x){
        for (int z = 0; z < CHUNK_SIZE; ++z){
            unsigned i[5] = {x * (CHUNK_SIZE * 2 + 1) + z, x * (CHUNK_SIZE * 2 + 1) + z + 1, x * (CHUNK_SIZE * 2 + 1) + z + CHUNK_SIZE + 1, (x + 1) * (CHUNK_SIZE * 2 + 1) + z, (x + 1) * (CHUNK_SIZE * 2 + 1) + z + 1};
            indices.push_back(i[0]); indices.push_back(i[2]); indices.push_back(i[1]);
            indices.push_back(i[1]); indices.push_back(i[2]); indices.push_back(i[4]);
            indices.push_back(i[4]); indices.push_back(i[2]); indices.push_back(i[3]);
            indices.push_back(i[3]); indices.push_back(i[2]); indices.push_back(i[0]);
        }
    }
    mesh.AddEBO(indices);
}
