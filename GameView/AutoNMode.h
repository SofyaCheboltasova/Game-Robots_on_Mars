#pragma once
#include "Menu.h"

class AutoNMode {
public:
    AutoNMode() = default;
    static void start(int N, std::string& s, Collector& collector, RenderWindow &app, RenderWindow &new_app, int numSteps);
};
