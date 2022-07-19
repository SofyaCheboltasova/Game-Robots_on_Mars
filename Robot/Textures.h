#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class Textures {
public:
    float w, h;
    sf::String File;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    Textures(sf::String F, float W, float H);
};