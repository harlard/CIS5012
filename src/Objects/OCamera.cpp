#include "OCamera.h"

OCamera::OCamera(){
  cam = nullptr;

}

OCamera::~OCamera(){
}

void OCamera::init(Vector3 newPos, Vector3 newLook, SceneManager* newScnMan){
  cam = newScnMan->createCamera("Test");
  SceneNode* rootNode;
  rootNode = newScnMan->getRootSceneNode();
  attachNodeTo(rootNode);
  setPositon(newPos);
  setLookAt(newLook);
  attachCamera(cam);
  }



Camera* OCamera::getCam(){
  return cam;
}

void OCamera::setAspect(float w, float h){
  cam->setAspectRatio(w / h);
}

void OCamera::update(){
  Vector3 newPos = getLooking();
  newPos.normalise();
  Vector3 cPos = getPosition();
  newPos = Vector3((cPos.x-((newPos.x)-1)),(cPos.y-((newPos.y)-1)),(cPos.z-((newPos.z)-1)));
  setPositon(newPos);
}
