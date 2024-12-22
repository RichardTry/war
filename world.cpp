#include "world.h"
#include "camera.h"

std::unordered_map<long long, Chunk> world;

sf::Shader world_shader;
Ogre::TerrainGroup terrain;

void InitWorld()
{
    mTerrainGroup = OGRE_NEW TerrainGroup(mSceneMgr, Terrain::ALIGN_X_Z, TERRAIN_SIZE, TERRAIN_WORLD_SIZE);
}

void setupTerrain()
{
    // create our main node to attach our entities to
    mObjectNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox", 5000);  // set our skybox

    setupLights();
    setupControls();
    
    // set our camera
    mCamera->setFOVy(Ogre::Degree(50.0));
    mCamera->setFOVy(Ogre::Degree(50.0));
    mCamera->setNearClipDistance(0.01f);
    mCamera->lookAt(Ogre::Vector3::ZERO);
    mCameraNode->setPosition(0, 0, 500);
    mCameraMan->setTopSpeed(100);

    setDragLook(true);

    // Set our camera to orbit around the origin at a suitable distance
    mCameraMan->setStyle(CS_ORBIT);
    mCameraMan->setYawPitchDist(Radian(0), Radian(0), 400);

    MaterialManager::getSingleton().setDefaultTextureFiltering(TFO_ANISOTROPIC);
    MaterialManager::getSingleton().setDefaultAnisotropy(7);

    mSceneMgr->setFog(FOG_LINEAR, ColourValue(0.7, 0.7, 0.8), 0, 4000, 10000);

    mTrayMgr->showCursor();
    
    mTerrainGlobals = OGRE_NEW TerrainGlobalOptions();

    mTerrainGroup = OGRE_NEW TerrainGroup(mSceneMgr, Terrain::ALIGN_X_Z, TERRAIN_SIZE, TERRAIN_WORLD_SIZE);
    mTerrainGroup->setFilenameConvention(TERRAIN_FILE_PREFIX, TERRAIN_FILE_SUFFIX);
    mTerrainGroup->setOrigin(mTerrainPos);
    mTerrainGroup->setAutoUpdateLod( TerrainAutoUpdateLodFactory::getAutoUpdateLod(BY_DISTANCE) ); // probably will do it in tessellation stages.
    
    Vector3 lightdir(0.55, -0.3, 0.75);
    lightdir.normalise();

    Light* l = mSceneMgr->createLight("tstLight");
    l->setType(Light::LT_DIRECTIONAL);
    l->setDirection(lightdir);
    l->setDiffuseColour(ColourValue::White);
    l->setSpecularColour(ColourValue(0.4, 0.4, 0.4));

    configureTerrainDefaults(l);

    mTerrainGroup->freeTemporaryResources();
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
    bool need_recalc = false;
    int view_dist = 10;
    for (int z = floor(camera->position.z / CHUNK_SIZE) - view_dist; z <= floor(camera->position.z / CHUNK_SIZE) + view_dist; ++z) {
        for (int x = floor(camera->position.x / CHUNK_SIZE) - view_dist; x <= floor(camera->position.x / CHUNK_SIZE) + view_dist; ++x) {
            long long key = coordsToKey(x, z);
            if (world.find(key) == world.end()) {
                world.emplace(std::piecewise_construct,
                    std::forward_as_tuple(key),
                    std::forward_as_tuple(x, z));
            }
            if (!world[key].generated) {
                need_recalc = true;
                world[key].Generate();
            }
        }
    }

    if (need_recalc) {
        for (int z = floor(camera->position.z / CHUNK_SIZE) - view_dist; z <= floor(camera->position.z / CHUNK_SIZE) + view_dist; ++z) {
            for (int x = floor(camera->position.x / CHUNK_SIZE) - view_dist; x <= floor(camera->position.x / CHUNK_SIZE) + view_dist; ++x) {
                long long key = coordsToKey(x, z);
                world[key].Recalculate();
            }
        }
    }

    for (int z = floor(camera->position.z / CHUNK_SIZE) - view_dist; z <= floor(camera->position.z / CHUNK_SIZE) + view_dist; ++z) {
        for (int x = floor(camera->position.x / CHUNK_SIZE) - view_dist; x <= floor(camera->position.x / CHUNK_SIZE) + view_dist; ++x) {
            long long key = coordsToKey(x, z);
            world_shader.setUniform("model", sf::Glsl::Mat4(
                glm::value_ptr(glm::translate(glm::mat4(1.0f), glm::vec3(x * (int)CHUNK_SIZE, 0, z * (int)CHUNK_SIZE)))
            ));

            std::cout << "Drawing " << x << "; " << z << std::endl;
            world_shader.setUniform("textures", world[key].textures);
            world[key].Draw();
            //sf::sleep(sf::milliseconds(20));

            //for ()//auto & obj : world[key].objects)
            //{
                //obj.render(target, content);
            //}
        }
    }
}
