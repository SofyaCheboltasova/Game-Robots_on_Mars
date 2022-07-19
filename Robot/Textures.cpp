#include "Textures.h"

Textures::Textures(sf::String F, float W, float H)  {
    File = F;
    w = W;
    h = H;
    image.loadFromFile(R"(C:\Users\sofya\Desktop\buttons\)" + File);
    texture. loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, w, h));
}
