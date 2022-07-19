#include "Sapper.h"
#include "../Dispatcher.h"

Sapper::Sapper() {
    w = 70; h = 70;
    image.loadFromFile(R"(C:\Users\sofya\Desktop\buttons\sapper_icon.png)");
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    i = 5000;
    j = 5000;
    x = i * 70;
    y = j * 70;
    sapautomode = 0;
    exist = false;
    wrongCoord = false;
    it1 = Dispatcher::scannedmap.begin();
    sprite.setTextureRect(IntRect(0, 0, w, h));
}