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
    public :
    OCamera();
    ~OCamera();
    void init(Vector3 newPos, Vector3 newLook, SceneManager* newScnMan);
    Vector3 getLook();
    Camera* getCam();
    void setAspect(float w, float h);



};

#endif
