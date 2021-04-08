#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>

#include "transform.h"
#include "chunk.h"
#include "content.h"

extern std::unordered_map<long long, Chunk> world;

void InitWorld();
void AddObject(int x, int y, Object & obj);
void UpdateWorld(const float & dt);
void DrawWorld(Transform * camera);

#endif // WORLD_H
