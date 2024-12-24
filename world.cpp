#include "world.h"
#include "camera.h"

std::unordered_map<long long, Chunk> world;

Shader world_shader;

using namespace Ogre;

World::World() {
    mTerrainGroup = OGRE_NEW TerrainGroup(scene_manager, Terrain::ALIGN_X_Z, TERRAIN_SIZE, TERRAIN_WORLD_SIZE);
}

void World::addOgreHead(const Vector3& position = Vector3(0,0,0), const Vector3& scale = Vector3(1, 1, 1), const Radian& rotation_angle = Radian(0)) {
    Entity* ogreEntity = this->scene_manager->createEntity("ogrehead.mesh");
    SceneNode* ogreNode = this->scene_manager->getRootSceneNode()->createChildSceneNode();
    ogreNode->setPosition(position);
    ogreNode->setScale(scale);
    ogreNode->roll(rotation_angle);
    ogreNode->attachObject(ogreEntity);
}

Camera* World::createCamera(const String& name, const float& near_clip_distance, const bool& auto_aspect_ratio) {
    Camera* cam = this->scene_manager->createCamera(name);
    cam->setNearClipDistance(near_clip_distance); // specific to this sample
    cam->setAutoAspectRatio(auto_aspect_ratio);
}

void World::setup() {
    this->scene_manager = root->createSceneManager();

    // register our scene with the RTSS
    // RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    // shadergen->addSceneManager(scene_manager);

    // -- tutorial section start --
    //! [turnlights]
    scene_manager->setAmbientLight(ColourValue(1.0, 0.5, 0.5));
    //! [turnlights]

    //! [newlight]
    Light* light = scene_manager->createLight("MainLight");
    SceneNode* lightNode = scene_manager->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject(light);
    //! [newlight]

    //! [lightpos]
    lightNode->setPosition(20, 80, 50);
    //! [lightpos]

    //! [camera]
    SceneNode* camNode = scene_manager->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Camera* cam = createCamera("myCam", 5, true);
    camNode->attachObject(cam);
    camNode->setPosition(16, 16, 32);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);
    //! [camera]

    this->addOgreHead();
    this->addOgreHead(Vector3(84, 48, 0));
    this->addOgreHead(Vector3(0, 104, 0), Vector3(2, 1.2, 1));
    this->addOgreHead(Vector3(-84, 48, 0), Vector3(0,0,0), Degree(-90));
}

void World::setupTerrain() {
    // create our main node to attach our entities to
    mObjectNode = scene_manager->getRootSceneNode()->createChildSceneNode();
    scene_manager->setSkyBox(true, "Examples/SpaceSkyBox", 5000);  // set our skybox

    setupLights();
    setupControls();
    
    // set our camera
    camera->setFOVy(Ogre::Degree(50.0));
    camera->setFOVy(Ogre::Degree(50.0));
    camera->setNearClipDistance(0.01f);
    camera->lookAt(Ogre::Vector3::ZERO);
    mCameraNode->setPosition(0, 0, 500);
    mCameraMan->setTopSpeed(100);

    setDragLook(true);

    // Set our camera to orbit around the origin at a suitable distance
    mCameraMan->setStyle(CS_ORBIT);
    mCameraMan->setYawPitchDist(Ogre::Radian(0), Ogre::Radian(0), 400);

    MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
    MaterialManager::getSingleton().setDefaultAnisotropy(7);

    scene_manager->setFog(Ogre::FOG_LINEAR, Ogre::ColourValue(0.7, 0.7, 0.8), 0, 4000, 10000);

    mTrayMgr->showCursor();
    
    mTerrainGlobals = OGRE_NEW TerrainGlobalOptions();

    mTerrainGroup = OGRE_NEW TerrainGroup(scene_manager, Ogre::Terrain::ALIGN_X_Z, TERRAIN_SIZE, TERRAIN_WORLD_SIZE);
    mTerrainGroup->setFilenameConvention(TERRAIN_FILE_PREFIX, TERRAIN_FILE_SUFFIX);
    mTerrainGroup->setOrigin(mTerrainPos);
    mTerrainGroup->setAutoUpdateLod( TerrainAutoUpdateLodFactory::getAutoUpdateLod(BY_DISTANCE) ); // probably will do it in tessellation stages.
    
    Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
    lightdir.normalise();

    Ogre::Light* l = scene_manager->createLight("tstLight");
    l->setType(Ogre::Light::LT_DIRECTIONAL);
    l->setDirection(lightdir);
    l->setDiffuseColour(Ogre::ColourValue::White);
    l->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));

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
    Shader::bind(&world_shader);
    world_shader.setUniform("projection", Glsl::Mat4(glm::value_ptr(projection)));
    world_shader.setUniform("view", Glsl::Mat4(glm::value_ptr(view)));
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
            world_shader.setUniform("model", Glsl::Mat4(
                glm::value_ptr(glm::translate(glm::mat4(1.0f), glm::vec3(x * (int)CHUNK_SIZE, 0, z * (int)CHUNK_SIZE)))
            ));

            std::cout << "Drawing " << x << "; " << z << std::endl;
            world_shader.setUniform("textures", world[key].textures);
            world[key].Draw();
            //sleep(milliseconds(20));

            //for ()//auto & obj : world[key].objects)
            //{
                //obj.render(target, content);
            //}
        }
    }
}
