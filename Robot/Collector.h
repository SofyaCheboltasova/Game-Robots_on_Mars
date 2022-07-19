#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Collector {
public:
    float x, y, w, h;
    int i = x, j = y, apples;
    static std::string mode;
    String File;
    Image image;
    Texture texture;
    Sprite sprite;
    bool colautomode;
    bool wrongCoord;
    std::map<int, char>::iterator it;
    int lastCell;
    Collector();
    std::map <int, char> collMap;
    void addCoordinates(int idx, char s);
};