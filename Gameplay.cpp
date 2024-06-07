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

    // Define the camera to look into our 3d world (position, target, up vector)
    camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 4.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    cameraMode = CAMERA_FIRST_PERSON;

    this->tethered = true;
    this->drawDeveloperTools = true;
}

GameScreen Gameplay::Loop(Vector3 positions[MAX_COLUMNS], float heights[MAX_COLUMNS], Color colours[MAX_COLUMNS]) {
    // Update
    //----------------------------------------------------------------------------------
    // Switch camera mode
    if (IsKeyPressed(KEY_ONE))
    {
        cameraMode = CAMERA_FREE;
        camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
    }

    if (IsKeyPressed(KEY_TWO))
    {
        cameraMode = CAMERA_FIRST_PERSON;
        camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
    }

    if (IsKeyPressed(KEY_THREE))
    {
        cameraMode = CAMERA_THIRD_PERSON;
        camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
    }

    if (IsKeyPressed(KEY_FOUR))
    {
        cameraMode = CAMERA_ORBITAL;
        camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
    }

    if (IsKeyPressed(KEY_FIVE)){
        tethered = !tethered;
    }

    if (IsKeyPressed(96)){
        drawDeveloperTools = !drawDeveloperTools;
    }

    std::cout << GetKeyPressed() << std::endl;

    // Switch camera projection
    if (IsKeyPressed(KEY_P))
    {
        if (camera.projection == CAMERA_PERSPECTIVE)
        {
            // Create isometric view
            cameraMode = CAMERA_THIRD_PERSON;
            // Note: The target distance is related to the render distance in the orthographic projection
            camera.position = (Vector3){ 0.0f, 2.0f, -100.0f };
            camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };
            camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
            camera.projection = CAMERA_ORTHOGRAPHIC;
            camera.fovy = 20.0f; // near plane width in CAMERA_ORTHOGRAPHIC
            CameraYaw(&camera, -135 * DEG2RAD, true);
            CameraPitch(&camera, -45 * DEG2RAD, true, true, false);
        }
        else if (camera.projection == CAMERA_ORTHOGRAPHIC)
        {
            // Reset to default view
            cameraMode = CAMERA_THIRD_PERSON;
            camera.position = (Vector3){ 0.0f, 2.0f, 10.0f };
            camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };
            camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
            camera.projection = CAMERA_PERSPECTIVE;
            camera.fovy = 60.0f;
        }
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

    // Update camera computes movement internally depending on the camera mode
    // Some default standard keyboard/mouse inputs are hardcoded to simplify use
    // For advance camera controls, it's reecommended to compute camera movement manually
    //UpdateCamera(&camera, cameraMode);                  // Update camera


    // Camera PRO usage example (EXPERIMENTAL)
    // This new camera function allows custom movement/rotation values to be directly provided
    // as input parameters, with this approach, rcamera module is internally independent of raylib inputs
    UpdateCameraPro(&camera,
                    (Vector3){
                            (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))*0.1f -      // Move forward-backward
                            (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))*0.1f,
                            (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))*0.1f -   // Move right-left
                            (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))*0.1f,
                            (IsKeyDown(KEY_SPACE) && !tethered)*0.1f -                    // Move up-down
                            (IsKeyDown(KEY_LEFT_CONTROL) && !tethered)*0.1f
                    },
                    (Vector3){
                            GetMouseDelta().x*0.05f,                            // Rotation: yaw
                            GetMouseDelta().y*0.05f,                            // Rotation: pitch
                            (IsKeyDown(KEY_E))*0.1f -                     // Rotation: roll
                            (IsKeyDown(KEY_Q))*0.1f
                    },
                    GetMouseWheelMove()*2.0f);                              // Move to target (zoom)

    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode3D(camera);

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

    // Draw player cube
    if (cameraMode == CAMERA_THIRD_PERSON)
    {
        DrawCube(camera.target, 0.5f, 0.5f, 0.5f, PURPLE);
        DrawCubeWires(camera.target, 0.5f, 0.5f, 0.5f, DARKPURPLE);
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
        DrawText(TextFormat("- Mode: %s", (cameraMode == CAMERA_FREE) ? "FREE" :
                                          (cameraMode == CAMERA_FIRST_PERSON) ? "FIRST_PERSON" :
                                          (cameraMode == CAMERA_THIRD_PERSON) ? "THIRD_PERSON" :
                                          (cameraMode == CAMERA_ORBITAL) ? "ORBITAL" : "CUSTOM"),
                 currentScreenWidth - 190, 90, 10, BLACK);
        DrawText(TextFormat("- Projection: %s", (camera.projection == CAMERA_PERSPECTIVE) ? "PERSPECTIVE" :
                                                (camera.projection == CAMERA_ORTHOGRAPHIC) ? "ORTHOGRAPHIC" : "CUSTOM"),
                 currentScreenWidth - 190, 105, 10, BLACK);
        DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", camera.position.x, camera.position.y,
                            camera.position.z), currentScreenWidth - 190, 120, 10, BLACK);
        DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", camera.target.x, camera.target.y, camera.target.z),
                 currentScreenWidth - 190, 135, 10, BLACK);
        DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", camera.up.x, camera.up.y, camera.up.z),
                 currentScreenWidth - 190, 150, 10, BLACK);
        DrawText(TextFormat("- Tethered: (%d)", tethered), currentScreenWidth - 190, 165, 10, BLACK);
    }

    EndDrawing();

    return GAMEPLAY;
}
