//
// Created by Josh on 13/06/2024.
//

#include "Collidable.h"

int Collidable::createBoundingBox(){
    this->objectsCollisionBox = (BoundingBox) {
        (Vector3) {
            collidablePosition.x - collidableSize.x/2,
            collidablePosition.y - collidableSize.y/2,
            collidablePosition.z - collidableSize.z/2},
        (Vector3) {
            collidablePosition.x + collidableSize.x/2,
            collidablePosition.y + collidableSize.y/2,
            collidablePosition.z + collidableSize.z/2}
    };

    return 1;
}

bool Collidable::checkCuboidCollision(BoundingBox toCheckAgainst) {
    return CheckCollisionBoxes(objectsCollisionBox, toCheckAgainst);
}

bool Collidable::checkSphereCollision(Vector3 toCheckAgainst, float radius) {
    return CheckCollisionBoxSphere(objectsCollisionBox, toCheckAgainst, radius);
}

int Collidable::setCollisionShape(shapes collisionShape){
    this->shape = collisionShape;
    return 1;
}

int Collidable::setCollisionSize(Vector3 size){
    this->collidableSize = size;
    return 1;
}

int Collidable::setCollisionPosition(Vector3 position){
    this->collidablePosition = position;
    createBoundingBox();
    return 1;
}

int Collidable::setCollisionRotation(Matrix rotation){
    this->collidableRotation = rotation;
    return 1;
}

// Overloaded checkCollision, so it smartly decides what type of collision may be occurring by the parameters passed in to it.
bool Collidable::checkCollision(BoundingBox toCheckAgainst) {
    return checkCuboidCollision(toCheckAgainst);
}

bool Collidable::checkCollision(Vector3 toCheckAgainst, float radius) {
    return checkSphereCollision(toCheckAgainst, radius);
}

Collidable::Collidable(shapes shape, Vector3 size, Vector3 position, Matrix rotation){
    std::cout << "Initialising Collisions with rotation" << std::endl;
    setCollisionShape(shape);
    setCollisionSize(size);
    setCollisionPosition(position);
    setCollisionRotation(rotation);

    std::cout << "shape " << shape << " size: x=" << size.x << " y=" << size.y << " z=" << size.z <<
    " position: x=" << position.x << " y=" << position.y << " z=" << position.z << std::endl;

    createBoundingBox();
}

Collidable::Collidable(shapes shape, Vector3 size, Vector3 position){
    std::cout << "Initialising Collisions" << std::endl;
    setCollisionShape(shape);
    setCollisionSize(size);
    setCollisionPosition(position);

    std::cout << "shape " << shape << " size: x=" << size.x << " y=" << size.y << " z=" << size.z <<
              " position: x=" << position.x << " y=" << position.y << " z=" << position.z << std::endl;

    createBoundingBox();
}

int Collidable::onCollision(BoundingBox box) {
    return 0;
}
