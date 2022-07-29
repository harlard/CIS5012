#include "OCamera.h"

OCamera::OCamera(){
  cam = nullptr;

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
  //attachCamara(ogreNode);


  }

void OCamera::attachToVP(Viewport *newVp){

}

Camera OCamera::getCam(){
  return *cam;
}
