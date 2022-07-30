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
      float rotationSpeed;
    public :
    OCamera();
    ~OCamera();
    void init(Vector3 newPos, Vector3 newLook, SceneManager* newScnMan);
    Camera* getCam();
    void update();
    void setAspect(float w, float h);
    void moveForward();
    void moveToSide();
    void rotateCamera();
    void setSpeed(float newSpeed);
    void setRotationSpeed(float newSpeed);



};

#endif
