#ifndef PINGPONGBALL_H_
#define PINGPONGBALL_H_

#include "Ogre.h"
#include "Object4o.h"
#include "OgreCameraMan.h"


using namespace Ogre;
using namespace OgreBites;

class PingPongBall : public Object4o{
    private :
      bool hold;
      float iThrowS;
      float cThrowS;
      Vector3 iThrowD;
      Vector3 cThrowD;
      Vector3 throwP;

    public :
    void init(SceneManager* newScnMan, Vector3 newPos, Vector3 newSca);
    void createRigidBody(float mass);
    void newEntity(SceneManager* newScnMan);
    void throwB();
    void recover();
    void setTP(Vector3 newTP);
    void setTS(float newTS);
    void setTD(Vector3 newTD);
    void update();
    bool getHold();
    void incrementTS(float inc);
    void changeD(Vector3 nd);


};

#endif
