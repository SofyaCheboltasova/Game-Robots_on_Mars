#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Robot/Textures.h"
#include "../GameView/GraphicView.h"
#include "../GameView/AutoNMode.h"
#include "../GameView/AutoMode.h"
class Menu {
public:
    Menu() = default;
    void start(RenderWindow &app, int N, std::string& s);
};
