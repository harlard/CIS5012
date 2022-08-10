#include "PingPongBall.h"

void PingPongBall::init(SceneManager* newScnMan, Vector3 newPos, Vector3 newSca){
  setScnMan(newScnMan);
  setNewPosition(newPos); // set current position
  ogreNode->attachObject(objEnt);
  setNewScale(newSca); // set current scale
  boundingBoxFromOgre();
  hold = false;
  iThrowD = Vector3(1.0,0.0,0.0);
  cThrowD = iThrowD;
  iThrowS = 10000.0;
  cThrowS = iThrowS;

  }
void PingPongBall::newEntity(SceneManager* newScnMan){
  nameMesh = "PingPongBall.mesh";
  objEnt = newScnMan->createEntity(nameMesh);
  }

void PingPongBall::createRigidBody(float bodyMass)
{
  colShape = new btSphereShape(btScalar(getOgreBound().x/2.0f));

  /// Create Dynamic Objects

  startTransform.setIdentity();

  Quaternion quat2 = ogreNode->_getDerivedOrientation();
  startTransform.setRotation(btQuaternion(quat2.x, quat2.y, quat2.z, quat2.w));

  Vector3 pos = ogreNode->_getDerivedPosition();
  startTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
  setMass(bodyMass);

}

void PingPongBall::throwB(){
  hold = false;
  btVector3 force(-(cThrowD.x)*cThrowS, (cThrowD.y)*cThrowS, (cThrowD.z)*cThrowS);
  btVector3 push;

  btTransform trans;

  if (body && body->getMotionState())
  {
      //get the orientation of the rigid body in world space.
      body->getMotionState()->getWorldTransform(trans);
      btQuaternion orientation = trans.getRotation();

      //rotate the local force, into the global space.
      //i.e. push in down the local z.
      push = quatRotate(orientation, force);

      //activate the body, this is essential if the body
      //has gone to sleep (i.e. stopped moving/colliding).
      body->activate();

      //apply a force to the center of the body
      body->applyCentralForce(push);
  }
}

void PingPongBall::recover(){
  hold = true;
  ogreNode->setPosition(throwP);
  reposition(throwP);
  body->setActivationState(0);
  cThrowD = iThrowD;
  cThrowS = iThrowS;
}

void PingPongBall::setTP(Vector3 newTP){throwP = newTP;}
void PingPongBall::setTS(float newTS){iThrowS = newTS; cThrowS = iThrowS;}
void PingPongBall::setTD(Vector3 newTD){iThrowD = newTD; cThrowD = iThrowD;}
bool PingPongBall::getHold(){return hold;}

void PingPongBall::update()
{
  if(!hold){
   btTransform trans;
  if (body && body->getMotionState())
  {
    body->getMotionState()->getWorldTransform(trans);
    btQuaternion orientation = trans.getRotation();

    ogreNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
    ogreNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
  }}
}
