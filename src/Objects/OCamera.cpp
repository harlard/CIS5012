#include "OCamera.h"

OCamera::OCamera(){
  cam = nullptr;
  looking = Vector3(0.0, 0.0, 0.0);
}

OCamera::~OCamera(){
}

OCamera::void init(Vector3 newPos, Vector3 newLook, SceneManager* newScnMan, Viewport *newVp){
  cam = newScnMan->createCamera("Test");
  SceneNode* rootNode;
  rootNode = newScnMan->getRootSceneNode();
  ogreNode = rootNode->createChildSceneNode();
  postion = newPos;
  ogreNode = newScnMan->createChildSceneNode()
  ogreNode->setPosition(position);
  looking = newCLook;
  ogreNode->lookAt(looking, Node::TransformSpace::TS_WORLD);
  ogreNode->attachObject(cam);
  attachToVP(newVp);
  attachTo()


  }

OCamera::void attachToVP(Viewport *newVp){
  newVp = getRenderWindow()->addViewport(cam);
  cam0->setAspectRatio(Real(newVp->getActualWidth()) / Real(newVp->getActualHeight()));

}

OCamera::Vector3 getCLook(){
 return looking;
}

OCamera::Camera getCam(){
  return cam;
}

OCamera::void setLookAt(Vector3 newCLook){
  ogreNode->lookAt(newCLook, Node::TransformSpace::TS_WORLD);

}
