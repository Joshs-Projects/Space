//
// Created by Josh on 14/06/2024.
//

#ifndef SPACE_CUBOID_H
#define SPACE_CUBOID_H

#include "Collidable.h"

class Cuboid : public Collidable {
private:
    //Vector3 positions = {0, 0, 0};
    Color colour = RED;

public:
    Cuboid(shapes shape, Vector3 size, Vector3 position, Color colour);

    int draw();

    Color getColour(){return colour;};


};


#endif //SPACE_CUBOID_H
