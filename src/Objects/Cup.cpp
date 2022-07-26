#include "Cup.h"

void Cup::init(SceneManager* newScnMan, Vector3 newPos, Vector3 newSca){
  setScnMan(newScnMan);
  setNewPosition(newPos); // set current position
  ogreNode->attachObject(objEnt);
  setNewScale(newSca); // set current scale
  boundingBoxFromOgre();
}
void Cup::newEntity(SceneManager* newScnMan){
  nameMesh = "Cup.mesh";
  objEnt = newScnMan->createEntity(nameMesh);
  }
/*
void Cup::createRigidBody(float bodyMass)
{
  colShape = new btSphereShape(btScalar(getOgreBound().x/2.0f));

  /// Create Dynamic Objects

  startTransform.setIdentity();

  Quaternion quat2 = ogreNode->_getDerivedOrientation();
  startTransform.setRotation(btQuaternion(quat2.x, quat2.y, quat2.z, quat2.w));

  Vector3 pos = ogreNode->_getDerivedPosition();
  startTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
  setMass(bodyMass);

}*/
