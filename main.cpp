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

#include "Title.h"
#include "Gameplay.h"
#include "structures.h"
#include "Cuboid.h"
#include <omp.h>


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    //Testing OpenMP
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        std::cout << "Hello from thread " << thread_id << std::endl;
    }
    return 0;

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    int currentScreenWidth = screenWidth;
    int currentScreenHeight = screenHeight;

    TitleScreen titleScreen;

    GameScreen currentScreen = GAMEPLAY;

    Gameplay gameplay(screenWidth, screenHeight);

    InitWindow(screenWidth, screenHeight, "Space");

    std::vector<Cuboid> cuboidObjects = {};

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


        //cuboidObjects.emplace_back(cuboid, size, position, colours[i % MAX_COLUMNS]); //Uses specific colour array to help with debugging
        cuboidObjects.emplace_back(cuboid, size, position, colour);
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
                currentScreen = gameplay.Loop(cuboidObjects);
                break;
            }
            case QUIT:
            {
                break;
            }
        }


        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
