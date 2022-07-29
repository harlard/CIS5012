#include "Object4o.h"
//add funtionality
Object4o::Object4o(){

  ogreNode = nullptr;
  objEnt = nullptr;

  colShape = nullptr;
  dynamicsWorld =  nullptr;

  Vector3 ogreBound(0.0f,0.0f,0.0f);

  linearDamping = 0.2f;
  angularDamping = 0.8f;
}

Object4o::~Object4o(){} // Weird!!!!

void Object4o::init(SceneManager* newScnMan, Vector3 newPos, Vector3 newSca){
  setScnMan(newScnMan);
  setPositon(newPos); // set current position
  setScale(newSca); // set current scale

}
void Object4o::setScnMan(SceneManager* newScnMan){
  newEntity(newScnMan);// set mesh by using a string parameter
  attachToRoot(newScnMan);

}

void Object4o::newEntity(SceneManager* newScnMan){
  nameMesh = "cube.mesh";
  objEnt = newScnMan->createEntity(nameMesh);
  }

void Object4o::setPositon(Vector3 newPos){
  position = newPos; // store current postion
  ogreNode->setPosition(position);//set postion in ogreNode

    }

void Object4o::setScale(Vector3 newSca){
  scale = newSca;
  ogreNode->setScale(newSca);
  }

void Object4o::setRotation(Vector3 axis, Radian rads){
  //quat from axis angle
Quaternion quat(rads, axis);
ogreNode->setOrientation(quat);

}
void Object4o::attachToRoot(SceneManager* newScnMan){
   SceneNode* rootNode;
   rootNode = newScnMan->getRootSceneNode();
   attachNodeTo(rootNode);
   ogreNode->attachObject(objEnt);
   ogreNode->setScale(1.0f,1.0f,1.0f);
   boundingBoxFromOgre();
}
void Object4o::boundingBoxFromOgre()
{
  //get bounding box here.
  ogreNode->_updateBounds();
  const AxisAlignedBox& b = ogreNode->_getWorldAABB();
  Vector3 temp(b.getSize());
  ogreBound = temp;
}
void Object4o::setMass(float newMass){
  cMass = newMass;
  btScalar mass(cMass);


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
  body->setUserPointer((void*)this);}
void Object4o::createRigidBody(float bodyMass)
{
  colShape = new btBoxShape(btVector3(ogreBound.x/2.0f, ogreBound.y/2.0f, ogreBound.z/2.0f));

  /// Create Dynamic Objects

  startTransform.setIdentity();

  Quaternion quat2 = ogreNode->_getDerivedOrientation();
  startTransform.setRotation(btQuaternion(quat2.x, quat2.y, quat2.z, quat2.w));

  Vector3 pos = ogreNode->_getDerivedPosition();
  startTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));


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

    ogreNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
    ogreNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
  }
}

void Object4o::attachNodeTo(SceneNode *nodeTo){ogreNode = nodeTo->createChildSceneNode();}

Vector3 Object4o::getPosition(){return position;}
Vector3 Object4o::getScale(){return scale;}
void Object4o::getRotaion(){}
Vector3 Object4o::getAxis(){return axis;}
Radian Object4o::getRad(){return rads;}
Vector3 Object4o::getOgreBound(){return ogreBound;}
SceneNode Object4o::getOgreNode(){return *ogreNode;}
void Object4o::getName(){}
float Object4o::getMass(){return cMass;}
void Object4o::setLookAt(Vector3 newLook){ looking = newLook; ogreNode->lookAt(looking, Node::TransformSpace::TS_WORLD);}
Vector3 Object4o::getLooking(){return looking;}
void Object4o::attachCamera(Camera *cam){ogreNode->attachObject(cam);}
