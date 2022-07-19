#pragma once
#include <sstream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "../Dispatcher.h"
#include "../GameView/Menu.h"

using namespace sf;

class GraphicGame {
public:
    GraphicGame() = default;
    void start(int N);
    void MoveKey(std::string& s, Event& e, Collector& collector, int N, View& view);
};
