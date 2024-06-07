//
// Created by Josh on 13/05/2024.
//

#include "raylib.h"
#include "rcamera.h"

#include <iostream>

#include "Gameplay.h"

Gameplay::Gameplay(int screenWidth, int screenHeight){
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    currentScreenWidth = screenWidth;
    currentScreenHeight = screenHeight;

    player = Player();

    this->drawDeveloperTools = true;
}

GameScreen Gameplay::Loop(Vector3 positions[MAX_COLUMNS], float heights[MAX_COLUMNS], Color colours[MAX_COLUMNS]) {
    // Update
    //----------------------------------------------------------------------------------
    // Switch camera mode
    if (IsKeyPressed(KEY_ONE))
    {
        player.changeToFreeCam();
    }

    if (IsKeyPressed(KEY_TWO))
    {
        player.changeToFirstPerson();
    }

    if (IsKeyPressed(KEY_THREE))
    {
        player.changeToThirdPerson();
    }

    if (IsKeyPressed(KEY_FOUR))
    {
        player.changeToOrbital();
    }

    if (IsKeyPressed(KEY_FIVE)){
        player.changeIfTethered();
    }

    if (IsKeyPressed(96)){
        drawDeveloperTools = !drawDeveloperTools;
    }

    // Switch camera projection
    if (IsKeyPressed(KEY_P))
    {
        player.switchCameraPerspective();
    }

    // Switch To Full Screen
    if (IsKeyPressed(KEY_ENTER) && IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)) {
        //Check the current display
        int display = GetCurrentMonitor();

        if (IsWindowFullscreen()) {
            //If at fullscreen then go back to windowed screen
            //Before changing the size it is necessary to toggle full screen first.
            ToggleFullscreen();
            currentScreenWidth = screenWidth;
            currentScreenHeight = screenHeight;
            SetWindowSize(800, 450);
            std::cout << "Screen Width: " << screenWidth << " Screen Height: " << screenHeight << "\n";
            std::cout << "Current Screen Width: " << currentScreenWidth << " Current Screen Height: " << currentScreenHeight << "\n";

        } else {
            //If not at full screen
            currentScreenWidth = GetMonitorWidth(display);
            currentScreenHeight = GetMonitorHeight(display);
            SetWindowSize(currentScreenWidth, currentScreenHeight);
            ToggleFullscreen();
        }

        //Toggle Fullscreen

    }

    if (IsKeyPressed(KEY_ESCAPE)){
        return QUIT;
    } else if (IsKeyPressed(KEY_T)){
        return TITLE;
    }

    player.updateCamera();

    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    //BeginMode3D(camera);
    BeginMode3D(player.getCamera());

    //Draws the walls and the floor
    DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY); // Draw ground
    DrawCube((Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);     // Draw a blue wall
    DrawCube((Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);      // Draw a green wall
    DrawCube((Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);      // Draw a yellow wall
    DrawCube((Vector3){ 0.0f, 2.5f, -16.0f }, 32.0f, 5.0f, 1.0f, PINK);      // Draw a yellow wall

    // Draw some cubes around
    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        DrawCube(positions[i], 2.0f, heights[i], 2.0f, colours[i]);
        DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
    }

    if (player.getCameraMode() == CAMERA_THIRD_PERSON)
    {
        DrawCube(player.getCamera().target, 0.5f, 0.5f, 0.5f, PURPLE);
        DrawCubeWires(player.getCamera().target, 0.5f, 0.5f, 0.5f, DARKPURPLE);
    }

    EndMode3D();

    if (drawDeveloperTools) {
        // Draw info boxes
        DrawRectangle(5, 5, 330, 100, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines(5, 5, 330, 100, BLUE);

        DrawText("Camera controls:", 15, 15, 10, BLACK);
        DrawText("- Move keys: W, A, S, D, Space, Left-Ctrl", 15, 30, 10, BLACK);
        DrawText("- Look around: arrow keys or mouse", 15, 45, 10, BLACK);
        DrawText("- Camera mode keys: 1, 2, 3, 4", 15, 60, 10, BLACK);
        DrawText("- Zoom keys: num-plus, num-minus or mouse scroll", 15, 75, 10, BLACK);
        DrawText("- Camera projection key: P", 15, 90, 10, BLACK);

        DrawRectangle(currentScreenWidth - 200, 5, 195, 175, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines(currentScreenWidth - 200, 5, 195, 175, BLUE);

        DrawText(TextFormat("FPS: %d", GetFPS()), currentScreenWidth - 190, 15, 10, BLACK);
        DrawText(TextFormat("Render Size/Screen Size:"), currentScreenWidth - 190, 30, 10, BLACK);
        DrawText(TextFormat("- Width: %d/%d", GetRenderWidth(), currentScreenWidth), currentScreenWidth - 190, 45, 10,
                 BLACK);
        DrawText(TextFormat("- Height: %d/%d", GetRenderHeight(), currentScreenHeight), currentScreenWidth - 190, 60,
                 10, BLACK);
        DrawText("Camera status:", currentScreenWidth - 190, 75, 10, BLACK);
        DrawText(TextFormat("- Mode: %s", (player.getCameraMode() == CAMERA_FREE) ? "FREE" :
                                          (player.getCameraMode() == CAMERA_FIRST_PERSON) ? "FIRST_PERSON" :
                                          (player.getCameraMode() == CAMERA_THIRD_PERSON) ? "THIRD_PERSON" :
                                          (player.getCameraMode() == CAMERA_ORBITAL) ? "ORBITAL" : "CUSTOM"),
                 currentScreenWidth - 190, 90, 10, BLACK);
        DrawText(TextFormat("- Projection: %s", (player.getCamera().projection == CAMERA_PERSPECTIVE) ? "PERSPECTIVE" :
                                                (player.getCamera().projection == CAMERA_ORTHOGRAPHIC) ? "ORTHOGRAPHIC" : "CUSTOM"),
                 currentScreenWidth - 190, 105, 10, BLACK);
        DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", player.getCamera().position.x, player.getCamera().position.y,
                            player.getCamera().position.z), currentScreenWidth - 190, 120, 10, BLACK);
        DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", player.getCamera().target.x, player.getCamera().target.y, player.getCamera().target.z),
                 currentScreenWidth - 190, 135, 10, BLACK);
        DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", player.getCamera().up.x, player.getCamera().up.y, player.getCamera().up.z),
                 currentScreenWidth - 190, 150, 10, BLACK);
        DrawText(TextFormat("- Tethered: (%d)", player.getIfTethered()), currentScreenWidth - 190, 165, 10, BLACK);
    }

    EndDrawing();

    return GAMEPLAY;
}
