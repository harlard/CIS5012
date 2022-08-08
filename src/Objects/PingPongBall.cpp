#include "PingPongBall.h"


void PingPongBall::createRigidBody(float bodyMass)
{
  colShape = new btBoxShape(btVector3(getOgreBound().x/2.0f, getOgreBound().y/2.0f, getOgreBound().z/2.0f));

  /// Create Dynamic Objects

  startTransform.setIdentity();

  Quaternion quat2 = ogreNode->_getDerivedOrientation();
  startTransform.setRotation(btQuaternion(quat2.x, quat2.y, quat2.z, quat2.w));

  Vector3 pos = ogreNode->_getDerivedPosition();
  startTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));


}
