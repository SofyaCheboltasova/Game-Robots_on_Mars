#include "Dispatcher.h"

std::map <int, Collector> Dispatcher::collectors;
std::map <int, Sapper> Dispatcher::sappers;
std::map <int, char> Dispatcher::scannedmap;

int Dispatcher::numberOfCol = 1;
int Dispatcher::numberOfSap = 0;
int Dispatcher::collectorId = 1;
int Dispatcher::sapperId = 1;
int Dispatcher::numSteps = 0;
int Dispatcher::apples = 0;
bool Dispatcher::automode = false;
int Dispatcher::autoId = -1;

int Dispatcher::countOfCol() {
    return numberOfCol;
}
void Dispatcher::addCollector(int id, Collector& collector) {
    collectors.insert({id, collector});
}

void Dispatcher::addCoordinates(int idx, char s){
    scannedmap.insert({idx, s});
}

void Dispatcher::addSapper(int id, Sapper& sapper) {
    sappers.insert({id, sapper});
}