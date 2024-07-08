//
// Created by Josh on 14/06/2024.
//

#include "Cuboid.h"

Cuboid::Cuboid(shapes shape, Vector3 size, Vector3 position, Matrix rotation, Color colour) : Collidable(shape, size, position, rotation) {
    this->colour = colour;
}

int Cuboid::draw() {
    return 1;
}