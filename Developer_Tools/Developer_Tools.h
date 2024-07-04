//
// Created by Josh on 04/07/2024.
//

#ifndef SPACE_DEVELOPER_TOOLS_H
#define SPACE_DEVELOPER_TOOLS_H

#include "raylib.h"
#include "../Player.h"

namespace Developer_Tools {

    class Developer_Tools {
    private:
        bool devTools = false;

    public:
        Developer_Tools(bool onOrOff);

        bool getDevTools(){ return devTools;};
        int setDevTools(bool devTools){ devTools = devTools; return 1;}
        bool flipDevTools() { devTools = !devTools; return devTools;}

        int Draw_Developer_Tools(Player player, int currentScreenWidth, int currentScreenHeight);

    };

} // Developer_Tools

#endif //SPACE_DEVELOPER_TOOLS_H
