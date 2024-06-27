//
// Created by Josh on 07/06/2024.
//

#ifndef SPACE_PLAYER_H
#define SPACE_PLAYER_H

#include "raylib.h"
#include "rcamera.h"

#include <iostream>
#include <cmath>

#include "Collidable.h"

class Player : public Collidable  {
private:
    Camera camera;
    CameraMode cameraMode;

    bool tethered = true;
    bool oldTethered = true;

    Vector3 position;
    Vector3 movement;
    Vector3 rotation;
    float zoom;

    Vector3 size;

    int updatePosition();
    int setPosition(Vector3 newPosition);
    int updateMovement();
    int updateRotation();
    int updateZoom();

    int updateAll();

public:
    Player(shapes shape, Vector3 size, Vector3 position);
    int changeToFreeCam();
    int changeToFirstPerson();
    int changeToThirdPerson();
    int changeToOrbital();

    int changeIfTethered();
    [[nodiscard]] bool getIfTethered() const;

    int switchCameraPerspective();

    int updateCamera();
    [[nodiscard]] Camera3D getCamera() const;
    [[nodiscard]] CameraMode getCameraMode() const;

    int onCollision(BoundingBox box) override;

};


#endif //SPACE_PLAYER_H
