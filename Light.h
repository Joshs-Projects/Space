//
// Created by Josh on 27/07/2024.
//

#ifndef SPACE_LIGHT_H
#define SPACE_LIGHT_H

#include "raylib.h"
#include "raymath.h"

#define MAX_LIGHTS 4

#define RLIGHTS_IMPLEMENTATION
/*
#include "rlights.h"
*/
#include "cmake-build-debug/_deps/raylib-src/examples/shaders/rlights.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION        330
#else
    #define GLSL_VERSION        100
#endif

class Light_ {
    private:
        Shader light_shader;

    public:
        Light_();

};


#endif //SPACE_LIGHT_H
