//
// Created by Josh on 12/05/2024.
//

#include <iostream>
#include "raylib.h"
#include "rcamera.h"

#include "Title.h"

TitleScreen::TitleScreen() {
    allButtons = {};
    Button quitButton {50, 50, 50, 50, "TEST", 10};
    allButtons.push_back(quitButton);
};

GameScreen TitleScreen::renderTitleScreen(int ScreenWidth, int ScreenHeight){
    ShowCursor();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText(TextFormat("FPS: %d", GetFPS()), ScreenWidth - 190, 15, 10, BLACK);


    for(int i = 0; i < allButtons.size(); i++){
        allButtons[i].drawButton();
    }
    EndDrawing();

    EnableEventWaiting();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        std::cout << "Mouse Button Clicked\n";
        Vector2 mouseXY = GetMousePosition();
        for (int i = 0; i < allButtons[i].drawButton(); i++){
            if (allButtons[i].detectCollision(mouseXY)){
                DisableEventWaiting();
                DisableCursor();
                return GAMEPLAY;
            } else {
                //No collision
            }
        }
    } else if (IsKeyPressed(KEY_ENTER)){
        HideCursor();
        DisableEventWaiting();
        return GAMEPLAY;
    } else if (IsKeyPressed(KEY_ESCAPE)){
        HideCursor();
        DisableEventWaiting();
        return QUIT;
    }

    return TITLE;
}

Button::Button(int xSize, int ySize, int xPos, int yPos, const char* text, int fontSize) {
    this->height = ySize;
    this->width = xSize;
    this->xPos = xPos;
    this->yPos = yPos;

    this->text = text;
    this->fontSize = fontSize;

    this->xPosText = xPos + fontSize/2;
    this->yPosText = yPos + fontSize/2;
}

Button::Button(int xPos, int yPos, const char *text, bool autoSize, int fontSize) {
    this->xPos = xPos;
    this->yPos = yPos;

    this->width = sizeof(text) + 1 * fontSize;
    this->height = fontSize * 2;

    this->text = text;
    this->fontSize = fontSize;

    this->xPosText = xPos + fontSize/2;
    this->yPosText = yPos + fontSize/2;
}

bool Button::detectCollision(Vector2 mouseXY) {
    if ((mouseXY.x >= xPos && mouseXY.x <= xPos+width)
        && (mouseXY.y >= yPos && mouseXY.y <= yPos+height)){
        std::cout << "COLLISION";
        return true;

    }
    std::cout << "NO COLLISION";
    return false;
}

bool Button::drawButton() {
    //BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawRectangle(xPos, yPos, width, height, BLUE);
    DrawText(text, xPosText, yPosText, fontSize, BLACK);

    //EndDrawing();
    return true;
}
