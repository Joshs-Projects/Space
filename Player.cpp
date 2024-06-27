//
// Created by Josh on 07/06/2024.
//

#include "Player.h"

Player::Player(shapes shape, Vector3 size, Vector3 position) : Collidable(shape, size, position) {
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

int Player::updatePosition() {
    Vector3 position = {getCamera().position.x,getCamera().position.y,getCamera().position.z};
    setCollisionPosition(position);
    std::cout << "Player Position x= " << position.x <<  " y= " << position.y << " z= " << position.z << std::endl;
    std::cout << "Collision Player Position x= " << position.x <<  "Collision  y= " << position.y << "Collision  z= " << position.z << std::endl;
    return 1;
}

int Player::setPosition(Vector3 newPosition) {

    camera.position.x = newPosition.x;
    //camera.position.y = newPosition.y;
    camera.position.z = newPosition.z;

    this->position.x = newPosition.x;
    //this->position.y = newPosition.y;
    this->position.z = newPosition.z;

    if (cameraMode != CAMERA_FIRST_PERSON){
        camera.position.y = newPosition.y;
        this->position.y = newPosition.y;
    };

    setCollisionPosition(this->position);
    return 1;
}

int Player::updateMovement() {
    movement = {0,0,0};
    //std::cout << "updating movement.x";
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) ||      // Move forward-backward
        IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
        movement.x = (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))*0.1f -      // Move forward-backward
                     (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))*0.1f;
    }
    //std::cout << "updating movement.y";
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ||   // Move right-left
        IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)){
        movement.y = (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))*0.1f -   // Move right-left
        (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))*0.1f;
    }
    //std::cout << "updating movement.z";
    if (IsKeyDown(KEY_SPACE) && !tethered ||                    // Move up-down
        IsKeyDown(KEY_LEFT_CONTROL) && !tethered){
        movement.z = (IsKeyDown(KEY_SPACE) && !tethered)*0.1f -                    // Move up-down
        (IsKeyDown(KEY_LEFT_CONTROL) && !tethered)*0.1f;
    }

    updatePosition();

    //std::cout << "updated movement" << std::endl;

    return 1;
}

int Player::updateRotation() {
    rotation = {0.0,0.0,0.0};
    //std::cout << "updating rotation.x";
    rotation.x = GetMouseDelta().x*0.05f;

    //std::cout << "updating rotation.y";
    rotation.y = GetMouseDelta().y*0.05f;

    //std::cout << "updating rotation.z";
    if (IsKeyDown(KEY_E) || IsKeyDown(KEY_Q)) {
        rotation.z = (IsKeyDown(KEY_E)*0.1f -                     // Rotation: roll
                     (IsKeyDown(KEY_Q)*0.1f));
    }

    if (IsKeyPressed(KEY_R)){
        rotation.z = rotation.z - rotation.z;
        std::cout << "Reset?";
    }
    //std::cout << "updated rotation" << std::endl;

    return 1;

}

int Player::updateZoom() {
    zoom = 0;
    zoom = GetMouseWheelMove()*2.0f;
    return 1;
}

int Player::updateAll(){
    //updatePosition();
    updateMovement();
    updateRotation();
    updateZoom();
    return 1;
}

int Player::updateCamera() {
    //std::cout << "Trying to update" << std::endl;
    updateAll();
    //std::cout << "Updated" << std::endl;
    // Camera PRO usage example (EXPERIMENTAL)
    // This new camera function allows custom movement/rotation values to be directly provided
    // as input parameters, with this approach, rcamera module is internally independent of raylib inputs
    UpdateCameraPro(&camera, movement, rotation, zoom);                              // Move to target (zoom)

    return 1;
}

Camera3D Player::getCamera() const{
    return camera;
}

CameraMode Player::getCameraMode() const{
    return this->cameraMode;
}

/*int Player::onCollision(BoundingBox collidedWith) {
    //Pythagoras
    Vector3 distanceToMax, distanceToMin;
    distanceToMax.x = std::sqrt(collidedWith.max.x * collidedWith.max.x + this->position.x * this->position.x);
    distanceToMax.y = std::sqrt(collidedWith.max.y * collidedWith.max.y + this->position.y * this->position.y);
    distanceToMax.z = std::sqrt(collidedWith.max.z * collidedWith.max.z + this->position.z * this->position.z);

    distanceToMin.x = std::sqrt(collidedWith.min.x * collidedWith.min.x + this->position.x * this->position.x);
    distanceToMin.y = std::sqrt(collidedWith.min.y * collidedWith.min.y + this->position.y * this->position.y);
    distanceToMin.z = std::sqrt(collidedWith.min.z * collidedWith.min.z + this->position.z * this->position.z);

    float overallDistanceMax = std::sqrt(distanceToMax.x * distanceToMax.x +
                                         distanceToMax.y * distanceToMax.y +
                                         distanceToMax.z * distanceToMax.z);

    float overallDistanceMin = std::sqrt(distanceToMin.x * distanceToMin.x +
                                         distanceToMin.y * distanceToMin.y +
                                         distanceToMin.z * distanceToMin.z);

    Vector3 newPosition;

    //Doesnt handle equidistance possible bug
    if (overallDistanceMax < overallDistanceMin) {
        if (distanceToMax.x < distanceToMax.y && distanceToMax.x < distanceToMax.z){
            newPosition.x = this->position.x - distanceToMax.x;
        } else if (distanceToMax.y < distanceToMax.x && distanceToMax.y < distanceToMax.z){
            newPosition.y = this->position.y - distanceToMax.y;
        } else if (distanceToMax.z < distanceToMax.x && distanceToMax.z < distanceToMax.y){
            newPosition.z = this->position.z - distanceToMax.z;
        }
    } else if (overallDistanceMin < overallDistanceMax) {
        if (distanceToMin.x < distanceToMin.y && distanceToMin.x < distanceToMin.z){
            newPosition.x = this->position.x - distanceToMin.x;
        } else if (distanceToMin.y < distanceToMin.x && distanceToMin.y < distanceToMin.z){
            newPosition.y = this->position.y - distanceToMin.y;
        } else if (distanceToMin.z < distanceToMin.x && distanceToMin.z < distanceToMin.y){
            newPosition.z = this->position.z - distanceToMin.z;
        }
    }

    setPosition(newPosition);

    std::cout << "Moving to get out of collision!" << std::endl;
    return 0;
}*/

int Player::onCollision(BoundingBox collidedWith) {
    //Determine the Overlap per axis
    float overlapX = std::min(collidedWith.max.x, getBoundingBox().max.x) -
                     std::min(collidedWith.min.x, getBoundingBox().min.x);

    float overlapY = std::min(collidedWith.max.y, getBoundingBox().max.y) -
                     std::min(collidedWith.min.y, getBoundingBox().min.y);

    float overlapZ = std::min(collidedWith.max.z, getBoundingBox().max.z) -
                     std::min(collidedWith.min.z, getBoundingBox().min.z);

    //Determine the MTV (Minimum Translation Vector)
    Vector3 MTV;
    if (overlapX < overlapY && overlapX < overlapZ) {
        // Resolve along the x-axis
        if (collidedWith.min.x < getBoundingBox().min.x) {
            MTV = {-overlapX, 0, 0};
        } else {
            MTV = {overlapX, 0, 0};
        }
    } else if (overlapY < overlapZ) {
        // Resolve along the y-axis
        if (collidedWith.min.y < getBoundingBox().min.y) {
            MTV = {0, -overlapY, 0};
        } else {
            MTV = {0, overlapY, 0};
        }
    } else {
        // Resolve along the z-axis
        if (collidedWith.min.z < getBoundingBox().min.z) {
            MTV = {0, 0, -overlapZ};
        } else {
            MTV = {0, 0, overlapZ};
        }
    }

    Vector3 newPosition;
    newPosition.x = newPosition.x + MTV.x;
    newPosition.y = newPosition.y + MTV.y;
    newPosition.z = newPosition.z + MTV.z;

    setPosition(newPosition);

    return 1;

}
