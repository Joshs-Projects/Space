//
// Created by Josh on 12/05/2024.
//

#ifndef SPACE_TITLE_H
#define SPACE_TITLE_H

#include <vector>

#include "structures.h"

class Button {
private:
    const char* text = "";
    int fontSize;

    int width;
    int height;

    int xPos;
    int yPos;

    int xPosText;
    int yPosText;


public:
    Button(int xSize, int ySize, int xPos, int yPos, const char* text, int fontSize);

    Button(int xPos, int yPos, const char* text, bool autoSize, int fontSize);

    bool detectCollision(Vector2 mouseXY);

    bool drawButton();

};

class TitleScreen {
private:
    std::vector<Button> allButtons{};

public:

    TitleScreen();
    GameScreen renderTitleScreen(int ScreenWidth, int ScreenHeight);

};

#endif
