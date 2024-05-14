//
// Created by Josh on 13/05/2024.
//

#ifndef SPACE_GAMEPLAY_H
#define SPACE_GAMEPLAY_H

#include "structures.h"


class Gameplay {
private:
    int screenWidth;
    int screenHeight;
    int currentScreenWidth;
    int currentScreenHeight;

    Camera camera;
    int cameraMode;

public:
    Gameplay(int screenWidth, int screenHeight);
    GameScreen Loop(Vector3 positions[MAX_COLUMNS], float heights[MAX_COLUMNS], Color colours[MAX_COLUMNS]);
};


#endif //SPACE_GAMEPLAY_H
