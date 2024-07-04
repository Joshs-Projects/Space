//
// Created by Josh on 04/07/2024.
//

#include "Developer_Tools.h"

namespace Developer_Tools {
    Developer_Tools::Developer_Tools(bool onOrOff) {
        devTools = onOrOff;
    }

    int Developer_Tools::Draw_Developer_Tools(Player player, int currentScreenWidth, int currentScreenHeight) {
        if (devTools) {
            //BeginDrawing();
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
            DrawText(TextFormat("- Width: %d/%d", GetRenderWidth(), currentScreenWidth), currentScreenWidth - 190, 45,
                     10,
                     BLACK);
            DrawText(TextFormat("- Height: %d/%d", GetRenderHeight(), currentScreenHeight), currentScreenWidth - 190,
                     60,
                     10, BLACK);
            DrawText("Camera status:", currentScreenWidth - 190, 75, 10, BLACK);
            DrawText(TextFormat("- Mode: %s", (player.getCameraMode() == CAMERA_FREE) ? "FREE" :
                                              (player.getCameraMode() == CAMERA_FIRST_PERSON) ? "FIRST_PERSON" :
                                              (player.getCameraMode() == CAMERA_THIRD_PERSON) ? "THIRD_PERSON" :
                                              (player.getCameraMode() == CAMERA_ORBITAL) ? "ORBITAL" : "CUSTOM"),
                     currentScreenWidth - 190, 90, 10, BLACK);
            DrawText(TextFormat("- Projection: %s",
                                (player.getCamera().projection == CAMERA_PERSPECTIVE) ? "PERSPECTIVE" :
                                (player.getCamera().projection == CAMERA_ORTHOGRAPHIC) ? "ORTHOGRAPHIC" : "CUSTOM"),
                     currentScreenWidth - 190, 105, 10, BLACK);
            DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", player.getCamera().position.x,
                                player.getCamera().position.y,
                                player.getCamera().position.z), currentScreenWidth - 190, 120, 10, BLACK);
            DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", player.getCamera().target.x,
                                player.getCamera().target.y, player.getCamera().target.z),
                     currentScreenWidth - 190, 135, 10, BLACK);
            DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", player.getCamera().up.x, player.getCamera().up.y,
                                player.getCamera().up.z),
                     currentScreenWidth - 190, 150, 10, BLACK);
            DrawText(TextFormat("- Tethered: (%d)", player.getIfTethered()), currentScreenWidth - 190, 165, 10, BLACK);

            //EndDrawing();
        }

        return 1;
    }
} // Developer_Tools