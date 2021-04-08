#ifndef CHUNK_H_INCLUDED
#define CHUNK_H_INCLUDED

#include <algorithm>
#include <vector>
#include <unordered_map>
#include "glm/glm.hpp"
#include "tile.h"
#include "object.h"
#include "unit.h"
#include "vao.h"

const unsigned int CHUNK_SIZE = 32;
const unsigned int CHUNK_FACTOR = 2;

class Chunk
{
    public:
    sf::Vector2i position;
    sf::Vector2i perlinVector;
    bool generated;
    Tile tiles[CHUNK_SIZE][CHUNK_SIZE];
    float height[CHUNK_SIZE][CHUNK_SIZE];
    std::vector<Object> objects;
    std::vector<Unit> units;

    VAO mesh;

    Chunk();
    ~Chunk();
    Chunk(int x, int y);

    void Update(const float & dt);
    void Draw();
    void Generate();
    void Recalculate();
};

long long coordsToKey(int x, int y);

#endif // CHUNK_H_INCLUDED
