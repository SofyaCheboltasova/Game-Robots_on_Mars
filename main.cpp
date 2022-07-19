#include "GameView/GraphicView.h"
#include <random>
#include <ctime>

//void GenerateMap(int N, int* map, const int* ar) {
//    std::ofstream out;
//    out.open(R"(C:\Users\sofya\Desktop\map.txt)");
//    srand(time(NULL));
//
//    for (size_t i = 0; i < N; ++i)
//        for(size_t j = 0; j < N; ++j) {
//            map[i * N + j] = (ar[rand() % 9]);
//
//            if(out.is_open())
//                out << map[i * N + j];
//        }
//}

int main() {
    int N = 10000;
//    int* map = new int[N * N];
//    int ar[] =  {0, 0, 0, 0, 0, 1, 2, 3, 3};
//    GenerateMap(N, map, ar);

    GraphicGame game;
    game.start(N);

    return 0;
}