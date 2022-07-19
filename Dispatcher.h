#pragma once
#include "Robot/Sapper.h"
#include "Robot/Collector.h"

class Dispatcher {
public:
    static int numberOfCol;
    static int numberOfSap;
    static int apples;
    static int collectorId;
    static int sapperId;
    static int numSteps;
    static bool automode;
    static int autoId;

    static std::map <int, Collector> collectors;
    static std::map <int, Sapper> sappers;
    static std::map <int, char> scannedmap;
    int countOfCol();
    static void addCollector(int id, Collector& collector);
    static void addSapper(int id, Sapper& sapper);
    static void addCoordinates(int idx, char s);
};


