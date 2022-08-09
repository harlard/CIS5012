#ifndef TABLE_H_
#define TABLE_H_

#include "Ogre.h"
#include "Object4o.h"


using namespace Ogre;

class Table : public Object4o{
    private :

    public :
    void newEntity(SceneManager* newScnMan);
  //  void initBullet(float mass, btAlignedObjectArray<btCollisionShape*> &collisionShapes);
};

#endif
