//
// Created by Josh on 13/05/2024.
//

#ifndef SPACE_GAMEPLAY_H
#define SPACE_GAMEPLAY_H

#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"
#include "rlgl.h"

#include <iostream>
#include <chrono>
#include <vector>

#include "structures.h"
#include "player.h"
#include "Cuboid.h"
#include "Developer_Tools/Developer_Tools.h"

#include "omp.h"


class Gameplay {
private:
    int screenWidth;
    int screenHeight;
    int currentScreenWidth;
    int currentScreenHeight;

    /*Camera camera;
    int cameraMode;

    bool tethered;
     */

    Developer_Tools::Developer_Tools devTools = Developer_Tools::Developer_Tools(true);

    //bool drawDeveloperTools;

    // This needs some work to get the player position and camera. Probably just include setting this in constructor
    Player player = Player(cuboid, (Vector3){1, 5, 1}, (Vector3){ 0.0f, 2.0f, 4.0f });

public:
    Gameplay(int screenWidth, int screenHeight);
    //GameScreen Loop(Vector3 positions[MAX_COLUMNS], float heights[MAX_COLUMNS], Color colours[MAX_COLUMNS]);
    GameScreen Loop(std::vector<Cuboid> cuboidObjects, std::vector<Matrix> rotationMatrices);
};


#endif //SPACE_GAMEPLAY_H
