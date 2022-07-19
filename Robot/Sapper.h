#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Sapper {
public:
    bool sapautomode;
    bool exist;
    bool wrongCoord;
    int lastBomb;
    float x, y, w, h;
    int i = x, j = y;
    String File;
    Image image;
    Texture texture;
    Sprite sprite;
    std::map<int, char>::iterator it1;
    Sapper();
};