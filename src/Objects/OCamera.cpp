#include "OCamera.h"

OCamera::OCamera(){
  cam = nullptr;

}

OCamera::~OCamera(){
}

void OCamera::init(Vector3 newPos, Vector3 newLook, SceneManager* newScnMan){
  setSpeed(10.0);
  setYRotation(Radian(1.0));
  setPRotaion(Radian(1.0));
  cam = newScnMan->createCamera("Test");
  SceneNode* rootNode;
  rootNode = newScnMan->getRootSceneNode();
  attachNodeTo(rootNode);
  yawNode = getOgreNode()->createChildSceneNode();
  pitchNode = yawNode->createChildSceneNode();
  rollNode = yawNode->createChildSceneNode();
  rollNode->attachObject(cam);
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

}

void OCamera::moveForward(){
  Vector3 newPos = getLooking();
  newPos.normalise();
  Vector3 cPos = getPosition();
  newPos = Vector3((cPos.x+((newPos.x)*movementSpeed)),(cPos.y+((newPos.y)*movementSpeed)),(cPos.z+((newPos.z)*movementSpeed)));
  setPositon(newPos);}

void OCamera::moveToSide(){}
void OCamera::setSpeed(float newSpeed){movementSpeed = newSpeed;}
// void OCamera::setRotationSpeed(float newSpeed){rotationSpeed = newSpeed;}
void OCamera::horizontalRotation(){}
void OCamera::verticalRotation(){
  Vector3 tAxis  = getLook();
  Radian tRad = (getRad() + yRotationSpeed);
  setRotation(tAxis, tRad);
}
void OCamera::setYRotation(Radian rad){yRotationSpeed = rad;}
void::OCamera::setPRotaion(Radian rad){pRotationSpeed = rad;}
void yawNodeRotation(){yawNode->yaw(-10.0);}
void pitchNodeRotation(){pitchNode->pitch(10.0)}
