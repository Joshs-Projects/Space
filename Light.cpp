//
// Created by Josh on 27/07/2024.
//

#include "Light.h"

Light_::Light_() {
    light_shader = LoadShader(TextFormat("resources/shaders/glsl%i/lighting.vs", GLSL_VERSION),
                        TextFormat("resources/shaders/glsl%i/lighting.fs", GLSL_VERSION));

    light_shader.locs[SHADER_LOC_VECTOR_VIEW];

    // Ambient light level (some basic lighting)
    int ambientLoc = GetShaderLocation(light_shader, "ambient");
    SetShaderValue(light_shader, ambientLoc, (float[4]){ 0.1f, 0.1f, 0.1f, 1.0f }, SHADER_UNIFORM_VEC4);

    // Create lights
    Light lights[MAX_LIGHTS] = { 0 };
    lights[0] = CreateLight(LIGHT_POINT, (Vector3){ -2, 1, -2 }, Vector3Zero(), YELLOW, light_shader);
    lights[1] = CreateLight(LIGHT_POINT, (Vector3){ 2, 1, 2 }, Vector3Zero(), RED, light_shader);
    lights[2] = CreateLight(LIGHT_POINT, (Vector3){ -2, 1, 2 }, Vector3Zero(), GREEN, light_shader);
    lights[3] = CreateLight(LIGHT_POINT, (Vector3){ 2, 1, -2 }, Vector3Zero(), BLUE, light_shader);
}
