#include "Object4o.h"
//add funtionality
Object4o::Object4o(){
ogreBound = nullptr;
colShape = nullptr;
dynamicsWorld =  nullptr;
body = nullptr
//douth
position = nullptr;
scale = nullptr;

}

Object4o::~Object4o(){} // Weird!!!!

void Object4o::init(SceneManager* newWorld, string newForm, Vector3 newPos, Vector3 newSca){
  setWorld(newWorld);// set new world(ogre manager)
  setForm(newForm);// set mesh by using a string parameter
  setPositon(newPos; // set current position
  setScale(newSca) // set current scale
  setBoundingForOgre()

}
void Object4o::setWorld(SceneManager* newWorld){
  world = newWorld;
}

void Object4o::setForm(string newFom){
  nameBody = newFom;
  body = world->createEntity(newFom);
  }

void Object4o::setPositon(Vector3 newPos){
  position = newPos; // store current postion
  nodeOgre->setPositon(position);//set postion in ogreNode

    }

void Object4o::setScale(vector3 newSca){
  scale = newSca;
  nodeOgre->setScale(newSca);
  }

void Object4o::setRotation(Vector3 axis, Radian rads){
  //quat from axis angle
Quaternion quat(rads, axis);
boxSceneNode->setOrientation(quat);

}
void Object4o::attachNode(SceneNode* parent){
  nodeOgre = parent->attachToNode(parent)

}
void Object4o::boundingBoxFromOgre()
{
  //get bounding box here.
  nodeOgre->_updateBounds();
  const AxisAlignedBox& b = nodeOgre->_getWorldAABB();
  Vector3 temp(b.getSize());
  ogreBound = temp;
}
void Object4o::createRigidBody(float bodyMass)
{
  colShape = new btBoxShape(btVector3(meshBoundingBox.x/2.0f, meshBoundingBox.y/2.0f, meshBoundingBox.z/2.0f));

  /// Create Dynamic Objects
  btTransform startTransform;
  startTransform.setIdentity();

  Quaternion quat2 = boxSceneNode->_getDerivedOrientation();
  startTransform.setRotation(btQuaternion(quat2.x, quat2.y, quat2.z, quat2.w));

  Vector3 pos = boxSceneNode->_getDerivedPosition();
  startTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));

  btScalar mass(bodyMass);

  //rigidbody is dynamic if and only if mass is non zero, otherwise static
  bool isDynamic = (mass != 0.f);

  btVector3 localInertia(0, 0, 0);
  if (isDynamic)
  {
      // Debugging
      //std::cout << "I see the cube is dynamic" << std::endl;
      colShape->calculateLocalInertia(mass, localInertia);
  }

  //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
  btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
  body = new btRigidBody(rbInfo);

  //Set the linear and angular damping
  //I'm using this to bring the object to rest when moving.
  //An alternative would be to use friciton for the collison.
  //No good for hovering stuff though.
  body->setDamping(linearDamping,angularDamping);

  //Set the user pointer to this object.
  body->setUserPointer((void*)this);
}

void Object4o::addToCollisionShapes(btAlignedObjectArray<btCollisionShape*> &collisionShapes)
{
  collisionShapes.push_back(colShape);
}

void Object4o::addToDynamicsWorld(btDiscreteDynamicsWorld* dynamicsWorld)
{
  this->dynamicsWorld = dynamicsWorld;
  dynamicsWorld->addRigidBody(body);
}

void Object4o::update()
{
  btTransform trans;

  if (body && body->getMotionState())
  {
    body->getMotionState()->getWorldTransform(trans);
    btQuaternion orientation = trans.getRotation();

    boxSceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
    boxSceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
  }
}
