#pragma once

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreApplicationContext.h"
#include "OgreCameraMan.h"
#include "Objects/Objects.h"
//#include "Utils/Utils.h"




/* Bullet3 Physics */
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"


using namespace Ogre;
using namespace OgreBites;


class Game : public ApplicationContext, public InputListener
{
private:
    SceneManager *scnMgr;
    PingPongBall *ball;
    RenderWindow* mWindow;
    OCamera *camO;
    Table *table;

  //  Object4o *object;
    //// collision configuration.
    btDefaultCollisionConfiguration *collisionConfiguration = new btDefaultCollisionConfiguration();

    /// use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    btCollisionDispatcher *dispatcher = new btCollisionDispatcher(collisionConfiguration);

    /// btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    btBroadphaseInterface *overlappingPairCache = new btDbvtBroadphase();

    /// the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    btSequentialImpulseConstraintSolver *solver = new btSequentialImpulseConstraintSolver;
    btDiscreteDynamicsWorld *dynamicsWorld;

    /// keep track of the shapes, we release memory at exit.
    // make sure to re-use collision shapes among rigid bodies whenever possible!
    btAlignedObjectArray<btCollisionShape *> collisionShapes;
    //Object4o *object;

public:
    Game();
    virtual ~Game();

    void setup();

    void setupCamera();
    void setupFloor();

    void setupLights();

    bool keyPressed(const KeyboardEvent &evt);
    bool mouseMoved(const MouseMotionEvent &evt);

    bool frameStarted(const FrameEvent &evt);
    bool frameEnded(const FrameEvent &evt);

    void bulletInit();
    void syncGraphicsToPhysics();
    void collisionDetection();
    void setupBall();
    void setupTable();
};
