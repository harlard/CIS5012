#ifndef OBJECT4O_H_
#define OBJECT4O_H_

/* Ogre3d Graphics*/
#include "Ogre.h"


/* Bullet3 Physics */
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"

using namespace Ogre;
using namespace std;

/** Example player class.
* Written to illistrate the connection of Ogre/Bullet.
* Essentially just a wrapper around the cube object setup code.
*/
class Object4o
{
    private:
    public:

      //ogre variable
      SceneNode* ogreNode; // node on ogre
      Entity* objEnt;// entity for ogre
      Vector3 ogreBound; //bound for ogre
      //bullet variable
      btCollisionShape* colShape; // collision shapes for bullet
      btRigidBody* body; // body for bullet
      btDiscreteDynamicsWorld* dynamicsWorld; // dynamic variable
      btScalar linearDamping; /**< Damping force on the linear motion of the body, kind of air/friction */
      btScalar angularDamping; /**< Damping force on the angular motion of the body, kind of air/friction */
      float cMass;   // Mass
      btTransform startTransform;
      // custom variables
      Vector3 position; // store current position
      Vector3 scale; // store current scale
      Vector3 axis; // store current axis
      Radian rads; // store current rads
      string nameMesh;// name of current form
      Vector3  looking;
      Object4o();
      ~Object4o();
      void virtual init(SceneManager* newScnMan, Vector3 newPos, Vector3 newSca);
      void virtual setScnMan(SceneManager* newScnMan); // attach to ogre node
      void virtual newEntity(SceneManager* newScnMan);// createMesh
      void setNewPosition(Vector3 newPos); //set a new position
      void setNewScale(Vector3 newSca); // set a new scale
      void setRotation(Vector3 axis,Radian rads); //set new rotation
      void setMass(); // set mass
      void  virtual update(); // update object
      void attachNodeTo(SceneNode *nodeTo); //attach to a new node
      void boundingBoxFromOgre(); // create border for ogre3d
      void  virtual createRigidBody(float mass); // set bullet
      void addToCollisionShapes(btAlignedObjectArray<btCollisionShape*> &collisionShapes); //Create a collider
      void addToDynamicsWorld(btDiscreteDynamicsWorld* dynamicsWorld); // add dynamics scnMan
      void setMass(float newMass); //set mass
      void setBoundingForOgre();
      Vector3 getCurrentPosition();
      Vector3 getCurrentScale();
      void getRotaion();
      Vector3 getAxis();
      Radian getRad();
      Vector3 getLook(){return looking;}
      Vector3 getOgreBound();
      SceneNode getOgreNode();
      void setLookAt(Vector3 newLook);
      float getMass();
      void getName();
      Vector3 getLooking();
      void attachCamera(Camera *cam);
      void attachThisNode(SceneNode *node);
      void  virtual initBullet(float mass, btAlignedObjectArray<btCollisionShape*> &collisionShapes, btDiscreteDynamicsWorld* dynamicsWorld);




};


#endif
