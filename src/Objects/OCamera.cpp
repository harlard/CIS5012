#include "OCamera.h"
#include <iostream>


OCamera::OCamera(){
  cam = nullptr;

}

OCamera::~OCamera(){
}

void OCamera::init(Vector3 newPos, Vector3 newLook, SceneManager* newScnMan){
  setSpeed(10.0);
  setYRotation(Radian(0.02));
  setPRotaion(Radian(0.02));
  cam = newScnMan->createCamera("Test");
  SceneNode* rootNode;
  rootNode = newScnMan->getRootSceneNode();
  camNode = rootNode->createChildSceneNode();
  camNode->setScale(1.0,1.0,1.0);
  camNode->setPosition(newPos);
  yawNode = camNode->createChildSceneNode();
  yawNode->setPosition(0.0,0.0,0.0);
  yawNode->setScale(1.0,1.0,1.0);
  pitchNode = yawNode->createChildSceneNode();
  pitchNode->setPosition(0.0,0.0,0.0);
  rollNode = pitchNode->createChildSceneNode();
  rollNode->setPosition(0.0,0.0,0.0 );
  rollNode->attachObject(cam);
  yawNode->yaw(Radian(1.57));
  pitchNode->pitch(Radian(-0.34));
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
/*  Vector3 newPos = getLooking();
  newPos.normalise();
  Vector3 cPos = getCurrentPosition();
  newPos = Vector3((cPos.x+((newPos.x)*movementSpeed)),(cPos.y+((newPos.y)*movementSpeed)),(cPos.z+((newPos.z)*movementSpeed)));
  camNode->setPosition(newPos);*/
/*  cam->moveRelative(0.0,1.0,0.0);*/}

void OCamera::moveToSide(){}
void OCamera::setSpeed(float newSpeed){movementSpeed = newSpeed;}
// void OCamera::setRotationSpeed(float newSpeed){rotationSpeed = newSpeed;}

void OCamera::setYRotation(Radian rad){yRotationSpeed = rad;}
void OCamera::setPRotaion(Radian rad){pRotationSpeed = rad;}
void OCamera::yawNodeRotation(bool dir){if(dir==true){yawNode->yaw(yRotationSpeed);}else{yawNode->yaw(-yRotationSpeed);}}
void OCamera::pitchNodeRotation(bool dir){if(dir==true){pitchNode->pitch(yRotationSpeed);}else{pitchNode->pitch(-yRotationSpeed);}}
