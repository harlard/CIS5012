#ifndef PINGPONGBALL_H_
#define PINGPONGBALL_H_

#include "Ogre.h"
#include "Object4o.h"
#include "OgreCameraMan.h"
#include "OgreApplicationContext.h"

using namespace Ogre;
using namespace OgreBites;

class PingPongBall : public Object4o{
    private :

    public :
    void init(SceneManager* newScnMan, Vector3 newPos, Vector3 newSca);
    void createRigidBody(float mass);
    void newEntity(SceneManager* newScnMan);
};

#endif
