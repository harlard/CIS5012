#ifndef OCAMERA_H_
#define OCAMERA_H_

#include "Ogre.h"
#include "Object4o.h"
#include "OgreCameraMan.h"
#include "OgreApplicationContext.h"

using namespace Ogre;
using namespace OgreBites;

class OCamera : public Object4o{
    private :
      Camera *cam;
      float movementSpeed;
      Radian yRotationSpeed;
      Radian pRotationSpeed;
      SceneNode *pitchNode; // use to do rotation in YZ
      SceneNode *yawNode;   //  use to do rotation in XZ
      SceneNode *rollnode;
    public :
    OCamera();
    ~OCamera();
    void init(Vector3 newPos, Vector3 newLook, SceneManager* newScnMan);
    Camera* getCam();
    void update();
    void setAspect(float w, float h);
    void moveForward();
    void moveToSide();
    void setSpeed(float newSpeed);
    void yawNodeRotation();
    void verticalRotation();
    void setYRotation(Radian rads);
    void setPRotaion(Radian rads);

};

#endif
