/*-------------------------------------------------------------------------
Significant portions of this project are based on the Ogre Tutorials
- https://ogrecave.github.io/ogre/api/1.10/tutorials.html
Copyright (c) 2000-2013 Torus Knot Software Ltd

Manual generation of meshes from here:
- http://wiki.ogre3d.org/Generating+A+Mesh

*/

#include <exception>
#include <iostream>

#include "Game.h"

using namespace Ogre;
using namespace std;

#include "OgreBullet.h"
using namespace std;

Game::Game() : ApplicationContext("BeerPong")
{
  dynamicsWorld = NULL;
  mWindow = nullptr;
  ball = nullptr;
  table = nullptr;
}

Game::~Game()
{
    // cleanup in the reverse order of creation/initialization

    ///-----cleanup_start----
    // remove the rigidbodies from the dynamics world and delete them

    for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
    {
        btCollisionObject *obj = dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody *body = btRigidBody::upcast(obj);

        if (body && body->getMotionState())
        {
            delete body->getMotionState();
        }

        dynamicsWorld->removeCollisionObject(obj);
        delete obj;
    }

    // delete collision shapes
    for (int j = 0; j < collisionShapes.size(); j++)
    {
        btCollisionShape *shape = collisionShapes[j];
        collisionShapes[j] = 0;
        delete shape;
    }

    // delete dynamics world
    delete dynamicsWorld;

    // delete solver
    delete solver;

    // delete broadphase
    delete overlappingPairCache;

    // delete dispatcher
    delete dispatcher;

    delete collisionConfiguration;

    // next line is optional: it will be cleared by the destructor when the array goes out of scope
    collisionShapes.clear();
}

void Game::setup()
{

    // do not forget to call the base first
//    ApplicationContext::createWindow("Game",1600,800, false/*Ogre::NameValuePairList  	miscParams = Ogre::NameValuePairList()*/);
  //  RenderWindow* mWindow = mRoot->createWindow("Main", 800, 600, false );
    ApplicationContext::setup();
    addInputListener(this);
//    ApplicationContext::RenderWindow* mWindow = mRoot->createRenderWindow("Main", 1600, 800, false );

    // get a pointer to the already created root
    //Root *root = new Root("root")
    scnMgr = getRoot()->createSceneManager();
    //windowResized();
    //RenderSystem::setConfigOptions("Video Mode","1600 x 800");


    // register our scene with the RTSS
    RTShader::ShaderGenerator *shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);
/*
	// tell Root not to load from any plugins or settings file
	Root *root = new Root("", "");

	// Load feature plugins. Scene managers will register
	// themselves for all scene types they support
	root->loadPlugin("Plugin_CgProgramManager");
	root->loadPlugin("Plugin_OctreeSceneManager");

	// load rendersystem plugin(s). The order is important in that GL
	// should be available on on platforms, while D3D9 would be available
	// only on Windows -- the try/catch will intercept the exception in this
	// case where D3D9 is not available and continue gracefully.

		// We can initialize Root here if we want. "false" tells Root NOT to create
		// a render window for us
		root->initialise(false);

		// set up the render window with all default params
		  mWindow->create(
			"Manual Ogre Window",	// window title
			800,					// window width, in pixels
			600,					// window height, in pixels
			false,					// fullscreen or not
			0);						// use defaults for all other values
      scnMgr = root->createSceneManager();
*/

		// from here you can set up your camera and viewports as normal
		// get a pointer to the default base scene manager -- sufficient for our purposes

		// create a single camera, and a viewport that takes up the whole window (default behavior


    bulletInit();

    setupCamera();

    setupFloor();

    setupLights();

    setupBall();

    setupTable();

}

void Game::setupCamera()
{
    // Setup viewport for the camera.
    Viewport *vp;
    camO = new OCamera();

    camO->init(Vector3(210.0,200.0,0.0), Vector3(0.0,0.5,1.0), scnMgr);

    vp = getRenderWindow()->addViewport(camO->getCam());
    camO->setAspect(Real(vp->getActualWidth()), Real(vp->getActualHeight()));
    vp->setBackgroundColour(ColourValue(0, 0, 0));

    // link the camera and view port.
}

void Game::bulletInit()
{
    /// collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
    collisionConfiguration = new btDefaultCollisionConfiguration();

    /// use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    dispatcher = new btCollisionDispatcher(collisionConfiguration);

    /// btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    overlappingPairCache = new btDbvtBroadphase();

    /// the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    solver = new btSequentialImpulseConstraintSolver;

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0, -100, 0));
}


void Game::setupFloor()
{

    // Create a plane
    Plane plane(Vector3::UNIT_Y, 0);

    // Define the plane mesh
    MeshManager::getSingleton().createPlane(
        "ground", RGN_DEFAULT,
        plane,
        1500, 1500, 20, 20,
        true,
        1, 5, 5,
        Vector3::UNIT_Z);

    // Create an entity for the ground
    Entity *groundEntity = scnMgr->createEntity("ground");

    // Setup ground entity
    //  Shadows off
    groundEntity->setCastShadows(false);

    // Material - Examples is the rsources file,
    // Rockwall (texture/properties) is defined inside it.
    groundEntity->setMaterialName("Examples/Rockwall");

    // Create a scene node to add the mesh too.
    SceneNode *thisSceneNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    thisSceneNode->attachObject(groundEntity);

    // the ground is a cube of side 100 at position y = 0.
    // the sphere will hit it at y = -6, with center at -5
    btCollisionShape *groundShape = new btBoxShape(btVector3(btScalar(750.), btScalar(50.), btScalar(750.)));

    collisionShapes.push_back(groundShape);

    btTransform groundTransform;
    groundTransform.setIdentity();
    //  groundTransform.setOrigin(btVector3(0, -100, 0));

    Vector3 pos = thisSceneNode->_getDerivedPosition();

    // Box is 100 deep (dimensions are 1/2 heights)
    // but the plane position is flat.
    groundTransform.setOrigin(btVector3(pos.x, pos.y - 50.0, pos.z));

    Quaternion quat2 = thisSceneNode->_getDerivedOrientation();
    groundTransform.setRotation(btQuaternion(quat2.x, quat2.y, quat2.z, quat2.w));

    btScalar mass(0.);

    // rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        groundShape->calculateLocalInertia(mass, localInertia);

    // using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState *myMotionState = new btDefaultMotionState(groundTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
    btRigidBody *body = new btRigidBody(rbInfo);

    //   body->setRestitution(0.0);

    // add the body to the dynamics world
    dynamicsWorld->addRigidBody(body);
}

bool Game::frameStarted(const Ogre::FrameEvent &evt)
{
    // Be sure to call base class - otherwise events are not polled.
    ApplicationContext::frameStarted(evt);
    //camO->moveForward();


    if (this->dynamicsWorld != NULL)
    {
        // Bullet can work with a fixed timestep
        // dynamicsWorld->stepSimulation(1.f / 60.f, 10);

        // Or a variable one, however, under the hood it uses a fixed timestep
        // then interpolates between them.

        dynamicsWorld->stepSimulation((float)evt.timeSinceLastFrame, 10);

        // Sync the graphics (ogre scene nodes) to the physics (bullet rigid bodies)
        syncGraphicsToPhysics();

        // Check for collisions.
        collisionDetection();
    }


    return true;
}

void Game::syncGraphicsToPhysics()
{

    // update positions of all objects
    for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
      {
          btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
          btRigidBody* body = btRigidBody::upcast(obj);
          btTransform trans;

          if (body && body->getMotionState())
          {
             body->getMotionState()->getWorldTransform(trans);

             /* https://oramind.com/ogre-bullet-a-beginners-basic-guide/ */
             void *userPointer = body->getUserPointer();

             // Player should know enough to update itself.
             if(userPointer == ball){ /* Ignore player, he's always updated!*/ }
             else if(userPointer == table){ /* Ignore player, he's always updated!*/ }
             else //This is just to keep the other objects working.
             {
               if (userPointer)
               {
                 btQuaternion orientation = trans.getRotation();
                 Ogre::SceneNode *sceneNode = static_cast<Ogre::SceneNode *>(userPointer);
                 sceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
                 sceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
               }
             }
           }
           else
           {
             trans = obj->getWorldTransform();
           }
      }

      //Update player here, his movement is not dependent on collisions.
      ball->update();
      table->update();
    }

void Game::collisionDetection()
{
    // collisions
    // from - https://forums.ogre3d.org/viewtopic.php?t=79853

    int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();

    if (numManifolds > 0)
    {
        std::cout << std::endl
                  << "*** COLLISION INFO ***" << std::endl;
        for (int i = 0; i < numManifolds; i++)
        {
            btPersistentManifold *contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
            const btCollisionObject *obA = contactManifold->getBody0();
            const btCollisionObject *obB = contactManifold->getBody1();

            int numContacts = contactManifold->getNumContacts();

            std::cout << "Contact Manifold: " << i << std::endl;

            if (numContacts > 0)
            {
                for (int k = 0; k < numContacts; k++)
                {
                    btManifoldPoint &pt = contactManifold->getContactPoint(k);
                    if (pt.getDistance() < 0.f)
                    {
                        // point of contact, handy for particle effects/decals etc.
                        const btVector3 &ptA = pt.getPositionWorldOnA();
                        const btVector3 &ptB = pt.getPositionWorldOnB();
                        const btVector3 &normalOnB = pt.m_normalWorldOnB;

                        // log to see the variation range of getAppliedImpulse and to chose the appropriate impulseThreshold
                        std::cout << "Contact point: " << k << std::endl;
                        std::cout << "With force:" << pt.getAppliedImpulse() << std::endl;
                    }
                }
            }
        }
    }
}

bool Game::frameEnded(const Ogre::FrameEvent &evt)
{
    if (this->dynamicsWorld != NULL)
    {
        // Bullet can work with a fixed timestep
        // dynamicsWorld->stepSimulation(1.f / 60.f, 10);

        // Or a variable one, however, under the hood it uses a fixed timestep
        // then interpolates between them.

        dynamicsWorld->stepSimulation((float)evt.timeSinceLastFrame, 10);
    }
    return true;
}

void Game::setupLights()
{
    // Setup Abient light
    scnMgr->setAmbientLight(ColourValue(1, 1, 1));
    scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);

    // Add a spotlight
    Light *spotLight = scnMgr->createLight("SpotLight");

    // Configure
    spotLight->setDiffuseColour(0, 0, 1.0);
    spotLight->setSpecularColour(0, 0, 1.0);
    spotLight->setType(Light::LT_SPOTLIGHT);
    spotLight->setSpotlightRange(Degree(35), Degree(50));

    // Create a schene node for the spotlight
    SceneNode *spotLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    spotLightNode->setDirection(0, -1, 0);
    spotLightNode->setPosition(Vector3(0, 200, 0));

    // Add spotlight to the scene node.
    spotLightNode->attachObject(spotLight);

    // Create directional light
    Light *directionalLight = scnMgr->createLight("DirectionalLight");

    // Configure the light
    directionalLight->setType(Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(ColourValue(0.4, 0, 0));
    directionalLight->setSpecularColour(ColourValue(0.4, 0, 0));

    // Setup a scene node for the directional lightnode.
    SceneNode *directionalLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    directionalLightNode->attachObject(directionalLight);
    directionalLightNode->setDirection(Vector3(0, -1, 1));

    // Create a point light
    Light *pointLight = scnMgr->createLight("PointLight");

    // Configure the light
    pointLight->setType(Light::LT_POINT);
    pointLight->setDiffuseColour(0.3, 0.3, 0.3);
    pointLight->setSpecularColour(0.3, 0.3, 0.3);

    // setup the scene node for the point light
    SceneNode *pointLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    // Configure the light
    pointLightNode->setPosition(Vector3(0, 150, 250));

    // Add the light to the scene.
    pointLightNode->attachObject(pointLight);
}

bool Game::keyPressed(const KeyboardEvent &evt)
{
    std::cout << "Got key event" << std::endl;
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    if (evt.keysym.sym == SDLK_UP)
    {
        camO->pitchNodeRotation(true);
      }
    if (evt.keysym.sym == SDLK_DOWN)
      {
          camO->pitchNodeRotation(false);
        }
    if (evt.keysym.sym == SDLK_RIGHT)
        {
          camO->yawNodeRotation(false);
          }
    if (evt.keysym.sym == SDLK_LEFT)
    {
        camO->yawNodeRotation(true);
      }
    if (evt.keysym.sym == SDLK_SPACE)
    {
        if(ball->getHold()){
          ball->throwB();
        }else{
          ball->recover();
        }
      }
    if (evt.keysym.sym == SDLK_KP_PLUS)
    {
        ball->incrementTS(100.0);
      }
    if (evt.keysym.sym == SDLK_KP_MINUS)
    {
        ball->incrementTS(-100.0);
      }
    if (evt.keysym.sym == SDLK_KP_6)
    {
        ball->changeD(Vector3(0.0,0.0,-0.01));
        }
    if (evt.keysym.sym == SDLK_KP_4)
    {
      ball->changeD(Vector3(0.0,0.0,0.01));
      }
    if (evt.keysym.sym == SDLK_KP_8)
    {
        ball->changeD(Vector3(0.0,0.01,0.0));
        }
    if (evt.keysym.sym == SDLK_KP_5)
    {
      ball->changeD(Vector3(0.0,-0.01,0.0));
      }

    return true;
}

bool Game::mouseMoved(const MouseMotionEvent &evt)
{
    std::cout << "Got Mouse" << std::endl;
    return true;
}

void Game::setupBall()
{
  ball = new PingPongBall();
  ball->init(scnMgr, Vector3(0.0,500.0,0.0),Vector3(1.0,1.0,1.0));
  ball->initBullet(1.0, collisionShapes, dynamicsWorld);
  ball->setNewRetitution(1.0);
  ball->setTP(Vector3(190.0,180.0,0.0));
}


void Game::setupTable()
{
  table = new Table();
  table->init(scnMgr, Vector3(0.0,100.0,0.0),Vector3(100.0,100.0,100.0));
  table->initBullet(0.0, collisionShapes, dynamicsWorld);
  table->setNewRetitution(0.8);
}
