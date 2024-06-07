//
// Created by Josh on 07/06/2024.
//

#ifndef SPACE_PLAYER_H
#define SPACE_PLAYER_H

#include "raylib.h"
#include "rcamera.h"
#include "iostream"

class Player {
private:
    Camera camera;
    CameraMode cameraMode;

    bool tethered = true;
    bool oldTethered = true;

public:
    Player();
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

};


#endif //SPACE_PLAYER_H
