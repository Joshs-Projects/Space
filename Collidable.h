//
// Created by Josh on 13/06/2024.
//

#ifndef SPACE_COLLIDABLE_H
#define SPACE_COLLIDABLE_H


#include "raylib.h"

#include <iostream>

enum shapes {
    cuboid,
    sphere
};

class Collidable {
private:
    Vector3 collidableSize;
    Vector3 collidablePosition;

    BoundingBox objectsCollisionBox;

    int createBoundingBox();

    bool checkCuboidCollision(BoundingBox toCheckAgainst);
    bool checkSphereCollision(Vector3 toCheckAgainst, float radius);

    shapes shape;

public:
    Collidable(shapes shape, Vector3 size, Vector3 position);

    int setCollisionShape(shapes shape);
    int setCollisionSize(Vector3 size);
    int setCollisionPosition(Vector3 position);

    bool checkCollision(BoundingBox toCheckAgainst); //Used for cuboids
    bool checkCollision(Vector3 toCheckAgainst, float radius); //Used for spheres

    virtual int onCollision(BoundingBox box);

    Vector3 getCollidableSize(){return collidableSize;};
    Vector3 getCollidablePosition(){return collidablePosition;};
    BoundingBox getBoundingBox(){return objectsCollisionBox;};

};


#endif //SPACE_COLLIDABLE_H
