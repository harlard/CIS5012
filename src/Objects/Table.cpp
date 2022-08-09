#include "Table.h"


void Table::newEntity(SceneManager* newScnMan){
  nameMesh = "Table.mesh";
  objEnt = newScnMan->createEntity(nameMesh);
  }
/*
void Table::initBullet(float mass, btAlignedObjectArray<btCollisionShape*> &collisionShapes){
  createRigidBody(mass);
  addToCollisionShapes(collisionShapes);
}*/
