#include "AutoMode.h"
//int checkColnColPos(int num){
//    for(int k = 0; k < 1000; k++) {
//        if (num != k && Dispatcher::collectors[num].x == Dispatcher::collectors[k].x &&
//            Dispatcher::collectors[num].y == Dispatcher::collectors[k].y)
//            return k;
//    }
//    return -1;
//}

int checkSapPos(int num){
    for(size_t k = 0; k <= Dispatcher::numberOfCol; k++) {
        if (num != k && Dispatcher::sappers[num].x == Dispatcher::collectors[k].x &&
            Dispatcher::sappers[num].y == Dispatcher::collectors[k].y)
            return k;
    }
    return -1;
}

int checkColPos(int num){
    for(size_t k = 0; k < 1000; k++) {
        if (num != k && Dispatcher::collectors[num].x == Dispatcher::sappers[k].x &&
            Dispatcher::collectors[num].y == Dispatcher::sappers[k].y)
            return k;
    }
    return -1;
}

int checkSapnSapPos(int num){
    for(size_t k = 0; k < 1000; k++) {
        if (num != k && Dispatcher::sappers[num].x == Dispatcher::sappers[k].x &&
            Dispatcher::sappers[num].y == Dispatcher::sappers[k].y)
            return k;
    }
    return -1;
}

void moveSap(std::string& s, int i, int j, int N, int k){
    if (s[(i - 1) * N + j] == '0') {
        Dispatcher::sappers[k].sprite.setPosition((i - 1) * 70, j * 70);
        Dispatcher::sappers[k].i = i - 1;
        Dispatcher::sappers[k].j = j;
        Dispatcher::sappers[k].x = Dispatcher::sappers[k].i * 70;
        Dispatcher::sappers[k].y = Dispatcher::sappers[k].j * 70;
    }
    else if (s[(i + 1) * N + j] == '0') {
        Dispatcher::sappers[k].sprite.setPosition((i + 1) * 70, j * 70);
        Dispatcher::sappers[k].i = i + 1;
        Dispatcher::sappers[k].j = j;
        Dispatcher::sappers[k].x = Dispatcher::sappers[k].i * 70;
        Dispatcher::sappers[k].y = Dispatcher::sappers[k].j * 70;
    }
    else if (s[i * N + (j + 1)] == '0') {
        Dispatcher::sappers[k].sprite.setPosition(i * 70, (j + 1) * 70);
        Dispatcher::sappers[k].i = i;
        Dispatcher::sappers[k].j = j + 1;
        Dispatcher::sappers[k].x = Dispatcher::sappers[k].i * 70;
        Dispatcher::sappers[k].y = Dispatcher::sappers[k].j * 70;
    }
}

void moveCol(std::string& s, int i, int j, int N, int k){
    if (s[(i - 1) * N + j] == '0' || s[(i - 1) * N + j] == '2') {
        Dispatcher::collectors[k].sprite.setPosition((i - 1) * 70, j * 70);
        Dispatcher::collectors[k].i = i - 1;
        Dispatcher::collectors[k].j = j;
        Dispatcher::collectors[k].x = Dispatcher::collectors[k].i * 70;
        Dispatcher::collectors[k].y = Dispatcher::collectors[k].j * 70;

        if (s[(i - 1) * N + j] == '2') {
            Dispatcher::apples++;
            s[(i - 1) * N + j] = '0';
        }

    } else if (s[(i + 1) * N + j] == '0' || s[(i + 1) * N + j] == '2') {
        Dispatcher::collectors[k].sprite.setPosition((i + 1) * 70, j * 70);
        Dispatcher::collectors[k].i = i + 1;
        Dispatcher::collectors[k].j = j;
        Dispatcher::collectors[k].x = Dispatcher::collectors[k].i * 70;
        Dispatcher::collectors[k].y = Dispatcher::collectors[k].j * 70;

        if (s[(i + 1) * N + j] == '2') {
            Dispatcher::apples++;
            s[(i + 1) * N + j] = '0';
        }
    } else if (s[i * N + (j + 1)] == '0' || s[i * N + (j + 1)] == '2') {
        Dispatcher::collectors[k].sprite.setPosition(i * 70, (j + 1) * 70);
        Dispatcher::collectors[k].i = i;
        Dispatcher::collectors[k].j = j + 1;
        Dispatcher::collectors[k].x = Dispatcher::collectors[k].i * 70;
        Dispatcher::collectors[k].y = Dispatcher::collectors[k].j * 70;

        if (s[i * N + (j + 1)] == '2') {
            Dispatcher::apples++;
            s[i * N + (j + 1)] = '0';
        }
    }
}

void AutoMode::startSap(std::string &s, RenderWindow &app, int num, std::map <int, char> :: iterator it_sap,  int N) {
    if(Dispatcher::sappers[num].wrongCoord == false && Dispatcher::sappers[num].it1->first == 50005000){
        Dispatcher::sappers[num].it1 = Dispatcher::scannedmap.begin();
        Dispatcher::sappers[num].wrongCoord = true;
    }

    if (it_sap->second == '0' || it_sap->second == '2') {
        Dispatcher::sappers[num].i = it_sap->first / N;
        Dispatcher::sappers[num].j = it_sap->first % N;
        int i = Dispatcher::sappers[num].i;
        int j = Dispatcher::sappers[num].j;
        Dispatcher::sappers[num].x = i * 70;
        Dispatcher::sappers[num].y = j * 70;

        // Столкновение сапера с другим роботом
        int k = checkSapPos(num);
        if (k != -1)
            moveCol(s, i, j, N, k);

        // Столкновение сапера с другим сапером
        int k1 = checkSapnSapPos(num);
        if (k1 != -1)
            moveSap(s, i, j, N, k1);

        // Столкновение двух саперов (возвращаются на последнюю обезвреженную бомбу)
        Dispatcher::sappers[num].it1++;
        if (Dispatcher::sappers[num].it1 == Dispatcher::scannedmap.end()){
            Dispatcher::sappers[num].i = Dispatcher::sappers[num].lastBomb / N;
            Dispatcher::sappers[num].j = Dispatcher::sappers[num].lastBomb % N;
            int i1 = Dispatcher::sappers[num].i;
            int j1 = Dispatcher::sappers[num].j;
            Dispatcher::sappers[num].x = i1 * 70;
            Dispatcher::sappers[num].y = j1 * 70;
            Dispatcher::sappers[num].sprite.setPosition(Dispatcher::sappers[num].x, Dispatcher::sappers[num].y);
        }

        else
            Dispatcher::sappers[num].sprite.setPosition(Dispatcher::sappers[num].x, Dispatcher::sappers[num].y);
        Dispatcher::sappers[num].it1--;
        }

    if (it_sap->second == '3') {
        Dispatcher::sappers[num].i = it_sap->first / N;
        Dispatcher::sappers[num].j = it_sap->first % N;
        int i = Dispatcher::sappers[num].i;
        int j = Dispatcher::sappers[num].j;
        Dispatcher::sappers[num].x = i * 70;
        Dispatcher::sappers[num].y = j * 70;
        Dispatcher::sappers[num].lastBomb =  i * N + j;
        Dispatcher::sappers[num].sprite.setPosition(Dispatcher::sappers[num].x, Dispatcher::sappers[num].y);

        s[i * N + j] = '0';
        it_sap->second = '0';
        Dispatcher::addCoordinates(i * N + j, s[i * N + j]);
    }
    app.draw(Dispatcher::sappers[num].sprite);
}

void AutoMode::startCol(std::string &s, RenderWindow &app, int num, std::map <int, char> :: iterator it_col,  int N){
    if(Dispatcher::collectors[num].wrongCoord == false && Dispatcher::collectors[num].it->first != Dispatcher::scannedmap.begin()->first){
        Dispatcher::collectors[num].it = Dispatcher::scannedmap.begin();
        Dispatcher::collectors[num].wrongCoord = true;
    }

    if(it_col->second == '0' || it_col->second == '2') {
        Dispatcher::collectors[num].i = it_col->first / N;
        Dispatcher::collectors[num].j = it_col->first % N;
        int i = Dispatcher::collectors[num].i;
        int j = Dispatcher::collectors[num].j;
        Dispatcher::collectors[num].x = i * 70;
        Dispatcher::collectors[num].y = j * 70;

        // Столкновение с другим сапером
        int k = checkColPos(num);
        if (k != -1)
            moveSap(s, i, j, N, k);

//        //Столкновение с другим роботом
//        int k1 = checkColnColPos(num);
//        if (k1 != -1)
//            moveCol(s, i, j, N, k1);

        if (it_col->second == '2') {
            s[i * N + j] = '0';
            it_col->second = '0';
            Dispatcher::addCoordinates(i * N + j, s[i * N + j]);
            Dispatcher::apples++;
        }

        Dispatcher::collectors[num].it++;
        // Робот останавливается около сапера
        if (Dispatcher::collectors[num].it == Dispatcher::scannedmap.end()) {
            if(s[(Dispatcher::sappers[num].lastBomb / N - 1) * N + Dispatcher::sappers[num].lastBomb % N] == '0') {
                Dispatcher::collectors[num].i = Dispatcher::sappers[num].lastBomb / N - 1;
                Dispatcher::collectors[num].j = Dispatcher::sappers[num].lastBomb % N;
            }
            else if(s[(Dispatcher::sappers[num].lastBomb / N + 1) * N + Dispatcher::sappers[num].lastBomb % N] == '0') {
                Dispatcher::collectors[num].i = Dispatcher::sappers[num].lastBomb / N + 1;
                Dispatcher::collectors[num].j = Dispatcher::sappers[num].lastBomb % N;
            }
            else if(s[Dispatcher::sappers[num].lastBomb / N * N + (Dispatcher::sappers[num].lastBomb % N - 1)] == '0') {
                Dispatcher::collectors[num].i = Dispatcher::sappers[num].lastBomb / N;
                Dispatcher::collectors[num].j = Dispatcher::sappers[num].lastBomb % N - 1;
            }
            if(s[Dispatcher::sappers[num].lastBomb / N * N + (Dispatcher::sappers[num].lastBomb % N + 1)] == '0') {
                Dispatcher::collectors[num].i = Dispatcher::sappers[num].lastBomb / N;
                Dispatcher::collectors[num].j = Dispatcher::sappers[num].lastBomb % N + 1;
            }

            int i1 = Dispatcher::collectors[num].i;
            int j1 = Dispatcher::collectors[num].j;
            Dispatcher::collectors[num].x = i1 * 70;
            Dispatcher::collectors[num].y = j1 * 70;
            Dispatcher::collectors[num].sprite.setPosition(Dispatcher::collectors[num].x, Dispatcher::collectors[num].y);
        }
        else
            Dispatcher::collectors[num].sprite.setPosition(Dispatcher::collectors[num].x, Dispatcher::collectors[num].y);

        Dispatcher::collectors[num].it--;
    }
        app.draw(Dispatcher::collectors[num].sprite);
}
