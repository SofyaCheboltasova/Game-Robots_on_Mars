#pragma once
#include "Menu.h"
using namespace sf;

class AutoMode {
 public:
    AutoMode() = default;
    static void startSap(std::string& s, RenderWindow &app, int num, std::map <int, char> :: iterator it_sap, int N);
    static void startCol(std::string &s, RenderWindow &app, int num, std::map <int, char> :: iterator it_col,  int N);

};

