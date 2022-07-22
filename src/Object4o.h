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
      //ogre variable
      SceneManager* world; // scene Manager from ogre
      SceneNode* nodeOgre // node on ogre
      Entity* objEnt;// entity for ogre
      Vector3 ogreBound; //bound for ogre
      //bullet variable
      btCollisionShape* colShape; // collision shapes for bullet
      btRigidBody* body; // body for bullet
      btDiscreteDynamicsWorld* dynamicsWorld; // dynamic variable
      // custom variables
      Vector3 position; // store current position
      SceneNode node; // node use in ogre
      Vector3 scale; // store current scale
      Vector3 axis; // store current axis
      Radian rads; // store current rads
      string nameBody;// name of current form

    public:
      Object4o();
      ~Object4o();
      void init(SceneManager* newWorld, string newForm, Vector3 newPos, Vector3 newSca):
      void setWorld(SceneManager* newWorld); // attach to ogre node
      void setForm(string newFom);// createMesh
      void setPositon(Vector3 newPos; //set a new position
      void setScale(Vector3 newSca); // set a new scale
      void setRotation(); //set new rotation
      void update(); // update object
      void attachToNode(); //attach to a new node
      void boundingBoxFromOgre(); // create border for ogre3d
      void createRigidBody(float mass); // set bullet
      void addToCollisionShapes(btAlignedObjectArray<btCollisionShape*> &collisionShapes); //Create a collider
      void addToDynamicsWorld(btDiscreteDynamicsWorld* dynamicsWorld); // add dynamics world
      void setMass(float mass); //set mass



};


#endif
