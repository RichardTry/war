#include "game.h"


Game::Game() : ApplicationContext("OgreTutorialApp") {}

void Game::addOgreHead(const Vector3& position = Vector3(0,0,0), const Vector3& scale = Vector3(1, 1, 1), const Radian& rotation_angle = 0) {
    Entity* ogreEntity = this->scnMgr->createEntity("ogrehead.mesh");
    SceneNode* ogreNode = this->scnMgr->getRootSceneNode()->createChildSceneNode();
    ogreNode->setPosition(position);
    ogreNode->setScale(scale);
    ogreNode->roll(rotation_angle);
    ogreNode->attachObject(ogreEntity);
}

Camera* Game::createCamera(const String& name, const float& near_clip_distance, const bool& auto_aspect_ratio) {
    Camera* cam = this->scnMgr->createCamera(name);
    cam->setNearClipDistance(near_clip_distance); // specific to this sample
    cam->setAutoAspectRatio(auto_aspect_ratio);
}

void Game::setup() {
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    Root* root = getRoot();
    this->scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    // RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    // shadergen->addSceneManager(scnMgr);

    // -- tutorial section start --
    //! [turnlights]
    scnMgr->setAmbientLight(ColourValue(1.0, 0.5, 0.5));
    //! [turnlights]

    //! [newlight]
    Light* light = scnMgr->createLight("MainLight");
    SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject(light);
    //! [newlight]

    //! [lightpos]
    lightNode->setPosition(20, 80, 50);
    //! [lightpos]

    //! [camera]
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

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


bool Game::keyPressed(const KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    return true;
}