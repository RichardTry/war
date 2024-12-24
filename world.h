#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <math.h>

#include "transform.h"
#include "chunk.h"
#include "content.h"
#include <Terrain/OgreTerrainGroup.h>

#define TERRAIN_SIZE 32
#define TERRAIN_WORLD_SIZE 10

class World {
    private:
        Ogre::Root* root;
        Ogre::SceneManager* scene_manager;
        Ogre::Camera* camera;

    public:
        std::unordered_map<long long, Chunk> world;
        Ogre::TerrainGroup *mTerrainGroup;

        World();
        void setup();
        Camera* createCamera(const String& name, const float& near_clip_distance, const bool& auto_aspect_ratio);
        void addOgreHead(const Vector3& position, const Vector3& scale, const Radian& rotation_angle);
        void setupTerrain();
        void AddObject(int x, int y, Object & obj);
        void UpdateWorld(const float & dt);
        void DrawWorld(Transform * camera);
};

#endif // WORLD_H
