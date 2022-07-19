#include "Collector.h"
#include "../Dispatcher.h"

std::string Collector::mode;
void Collector::addCoordinates(int idx, char s){
    collMap.insert({idx, s});
}

Collector::Collector() {
    w = 70; h = 70;
    image.loadFromFile(R"(C:\Users\sofya\Desktop\buttons\robot.png)" );
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    mode = "manual";
    i = 5000;
    j = 5000;
    x = i * 70;
    y = j * 70;
    apples = 0;
    colautomode = 0;
    wrongCoord = false;
    it = Dispatcher::scannedmap.begin();
    sprite.setTextureRect(IntRect(0, 0, w, h));
}

