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
      SceneNode *camNode;  // I got some problem using ogreNode from object4o ao i replace for this once
      SceneNode *pitchNode; // use to do rotation in YZ
      SceneNode *yawNode;   //  use to do rotation in XZ
      SceneNode *rollNode;
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
    void verticalRotation();
    void setYRotation(Radian rads);
    void setPRotaion(Radian rads);
    void pitchNodeRotation();
    void yawNodeRotation();


};

#endif
