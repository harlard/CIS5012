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
      Vector3  looking;

    public :
    OCamera();
    ~OCamera();
    void init(Vector3 newPos, Vector3 newLook, SceneManager* newScnMan, Viewport *newVp);
    void  setLookAt(Vector3 newCLook);
    Vector3 getLook();
    Camera getCam();
    void attachTo(SceneNode *nodeTo);


};

#endif
