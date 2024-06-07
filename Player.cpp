//
// Created by Josh on 07/06/2024.
//

#include "Player.h"

Player::Player() {
    // Define the camera to look into our 3d world (position, target, up vector)
    camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 4.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    cameraMode = CAMERA_FIRST_PERSON;

}

int Player::changeToFreeCam() {
    cameraMode = CAMERA_FREE;
    oldTethered = tethered;
    tethered = false;
    std::cout << tethered << std::endl;
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll

    return 1;
}

int Player::changeToFirstPerson() {
    cameraMode = CAMERA_FIRST_PERSON;
    tethered = oldTethered;
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll

    return 1;
}

int Player::changeToThirdPerson() {
    cameraMode = CAMERA_THIRD_PERSON;
    tethered = oldTethered;
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll

    return 1;
}

int Player::changeToOrbital() {
    cameraMode = CAMERA_ORBITAL;
    tethered = oldTethered;
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll

    return 1;
}

int Player::changeIfTethered() {
    tethered = !tethered;
    oldTethered = tethered;

    return 1;
}

bool Player::getIfTethered() const{
    return tethered;
}

int Player::switchCameraPerspective() {
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

    return 1;
}

int Player::updateCamera() {
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

    return 1;
}

Camera3D Player::getCamera() const{
    return camera;
}

CameraMode Player::getCameraMode() const{
    return this->cameraMode;
}
