/*******************************************************************************************
*
*   raylib [core] example - 3d camera first person
*
*   Example originally created with raylib 1.3, last time updated with raylib 1.3
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"

#include "Title.h"
#include "Gameplay.h"
#include "structures.h"
#include "Cuboid.h"
//#include "Light.h"

#include "Developer_Tools/LoggerMacros.h"
//#include "Developer_Tools/Logger.h"

#include <omp.h>
#include <thread>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    LOG_ENTRY();
    int n = std::thread::hardware_concurrency();
    omp_set_num_threads(n);
    //Testing OpenMP
    #pragma omp parallel
    {
        int threads = omp_get_num_threads();
        std::cout << "There are " << threads << " number of threads." << std::endl;
    }
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    int currentScreenWidth = screenWidth;
    int currentScreenHeight = screenHeight;

    TitleScreen titleScreen;

    GameScreen currentScreen = GAMEPLAY;

    Gameplay gameplay(screenWidth, screenHeight);

    SetConfigFlags(FLAG_MSAA_4X_HINT); //Enable Multi Sampling Anti Aliasing 4x (if available)

    InitWindow(screenWidth, screenHeight, "Space");

    Image icon = LoadImage("Resources/icon.png");

    SetWindowIcon(icon);

    UnloadImage(icon);


    std::vector<Cuboid> cuboidObjects = {};
    std::vector<Matrix> rotationMatrices = {};

    // Generates some random columns
    /*float heights[MAX_COLUMNS] = { 0 };
    Vector3 positions[MAX_COLUMNS] = { 0 };
    Color colors[MAX_COLUMNS] = { 0 };*/
    //Color colours[MAX_COLUMNS] = {RED , BROWN, BLUE, PINK, ORANGE};

    Vector3 size;
    Vector3 position;
    Color colour;

    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        size = (Vector3) {
            2.0f,
            (float)GetRandomValue(1, 12),
            2.0f
        };

        position = (Vector3){ (float)GetRandomValue(-15, 15),
                              size.y/2.0f,
                              (float)GetRandomValue(-15, 15) };

        colour = (Color){ (unsigned char)GetRandomValue(20, 255),
                          (unsigned char)GetRandomValue(10, 55),
                          30,
                          255 };

        //Matrix rotationMatrices =
        //Matrix rotMat = MatrixRotateXYZ((Vector3){ (float)GetTime() * (float)GetRandomValue(0, 1), 0.0f, (float)GetTime() * (float)GetRandomValue(0, 1) });
        Matrix matRotation = MatrixRotateXYZ((Vector3){ 0.0f, (float)GetTime() * (float)GetRandomValue(0, 1), 0.0f });

        Matrix matTranslateToOrigin = MatrixTranslate(-position.x, -position.y, -position.z);
        Matrix matTranslateBack = MatrixTranslate(position.x, position.y, position.z);

        // Combine translation and rotation
        Matrix matTransform = MatrixMultiply(MatrixMultiply(matTranslateToOrigin, matRotation), matTranslateBack);

        //Try to rotate a cube.
        rotationMatrices.emplace_back(matTransform);


        //cuboidObjects.emplace_back(cuboid, size, position, colours[i % MAX_COLUMNS]); //Uses specific colour array to help with debugging
        cuboidObjects.emplace_back(cuboid, size, position, matRotation, colour);
        //std::cout << "Colour = " << colours[i] << std::endl << "--------------------------------" << std::endl;
        /*heights[i] = (float)GetRandomValue(1, 12);
        position = (Vector3){ (float)GetRandomValue(-15, 15),
                                  heights[i]/2.0f,
                                  (float)GetRandomValue(-15, 15) };
        colors[i] = (Color){ (unsigned char)GetRandomValue(20, 255),
                             (unsigned char)GetRandomValue(10, 55),
                             30,
                             255 };*/
    }

    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(120);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    LOG_INFO("Entering the main game loop.");
    bool firstDraw = true;
    // Main game loop
    while (currentScreen != QUIT)        // Detect window close button or ESC key
    {
        switch(currentScreen){
            case TITLE:
            {
                currentScreen = titleScreen.renderTitleScreen(currentScreenWidth, currentScreenHeight);
                break;
            }
            case GAMEPLAY:
            {
                //currentScreen = gameplay.Loop(positions, heights, colors);
                currentScreen = gameplay.Loop(cuboidObjects, rotationMatrices, firstDraw);
                firstDraw = false;
                break;
            }
            case QUIT:
            {
                break;
            }
        }


        //----------------------------------------------------------------------------------
    }

    //Light();

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    LOG_EXIT();

    return 0;
}
