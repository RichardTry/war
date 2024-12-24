#ifndef CHUNK_H_INCLUDED
#define CHUNK_H_INCLUDED

#include <algorithm>
#include <vector>
#include <unordered_map>
#include <Ogre.h>
#include "tile.h"
#include "object.h"
#include "unit.h"

#define CHUNK_SIZE 32
#define PERLIN_VECTOR_MAX 2

class Chunk
{
    public:
    Ogre::Vector2 position;
    //glm::vec2 perlinVector;
    Ogre::Vector2 perlinVector;
    bool generated;
    Tile tiles[CHUNK_SIZE][CHUNK_SIZE];
    Ogre::Texture textures;
    float height[CHUNK_SIZE][CHUNK_SIZE];
    std::vector<Object> objects;
    std::vector<Unit> units;
    std::unordered_map<long long, Chunk>& world;

    Ogre::Entity mesh;

    Chunk();
    ~Chunk();
    Chunk(int x, int y);

    float GetHeight(int x, int z);
    float SGetHeight(int x, int z);

    void Update(const float & dt);
    void Generate();
    void Recalculate();
};

long long coordsToKey(int x, int y);

#endif // CHUNK_H_INCLUDED
