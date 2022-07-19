#include "GraphicView.h"
#include <time.h>
using namespace sf;

int checkColPos(int i, int j, int N){
    for(size_t k = 0; k < 1000; k++) {
        if (i * N + j != 50005000 && i == Dispatcher::sappers[k].i && j == Dispatcher::sappers[k].j)
            return k + 1;
    }
    return -1;
}

void GraphicGame::MoveKey(std::string& s, Event& e, Collector& collector, int N, View& view) {
    // Сканирование клеток от исходной позиции
    Dispatcher::addCoordinates(collector.i * N + collector.j, s[collector.i * N + collector.j]);
    collector.addCoordinates(collector.i * N + collector.j, s[collector.i * N + collector.j]);
    Dispatcher::addCoordinates((collector.i - 1) * N + collector.j, s[(collector.i - 1) * N + collector.j]);
    Dispatcher::addCoordinates((collector.i + 1) * N + collector.j, s[(collector.i + 1) * N + collector.j]);
    Dispatcher::addCoordinates(collector.i * N + (collector.j - 1), s[collector.i * N + (collector.j - 1)]);
    Dispatcher::addCoordinates(collector.i * N + (collector.j + 1), s[collector.i * N + (collector.j + 1)]);

    if (e.key.code == Keyboard::Left) {
        if(checkColPos(collector.i - 1, collector.j, N) == -1) {
            if (s[(collector.i - 1) * N + collector.j] != '1' && s[(collector.i - 1) * N + collector.j] != '3') {
                collector.addCoordinates((collector.i - 1) * N + collector.j, s[(collector.i - 1) * N + collector.j]);
                collector.sprite.move(-70, 0);
                collector.i--;
                collector.x = collector.i * 70;
                view.move(-70, 0);
            }
            if (s[collector.i * N + collector.j] == '2') {                    //кушанье яблок
                s[collector.i * N + collector.j] = '0';
                Dispatcher::apples++;
            }
        }
    }

    if(e.key.code == Keyboard::Right) {
        if(checkColPos(collector.i + 1, collector.j, N) == -1) {
            if (s[(collector.i + 1) * N + collector.j] != '1' && s[(collector.i + 1) * N + collector.j] != '3') {
                collector.addCoordinates((collector.i + 1) * N + collector.j, s[(collector.i + 1) * N + collector.j]);
                collector.sprite.move(70, 0);
                view.move(70, 0);
                collector.i++;
                collector.x = collector.i * 70;
            }
            if (s[collector.i * N + collector.j] == '2') {
                s[collector.i * N + collector.j] = '0';
                Dispatcher::apples++;
            }
        }
    }

    if(e.key.code == Keyboard::Up ) {
        if(checkColPos(collector.i, collector.j - 1, N) == -1) {
            if (s[collector.i * N + collector.j - 1] != '1' && s[collector.i * N + collector.j - 1] != '3') {
                collector.addCoordinates(collector.i * N + (collector.j - 1), s[collector.i * N + (collector.j - 1)]);
                collector.sprite.move(0, -70);
                view.move(0, -70);
                collector.j--;
                collector.y = collector.j * 70;
            }
            if (s[collector.i * N + collector.j] == '2') {
                s[collector.i * N + collector.j] = '0';
                Dispatcher::apples++;
            }
        }
    }

    if(e.key.code == Keyboard::Down) {
        if(checkColPos(collector.i, collector.j + 1, N) == -1) {
            if (s[collector.i * N + collector.j + 1] != '1' && s[collector.i * N + collector.j + 1] != '3') {
                collector.addCoordinates(collector.i * N + (collector.j + 1), s[collector.i * N + (collector.j + 1)]);
                collector.sprite.move(0, 70);
                view.move(0, 70);
                collector.j++;
                collector.y = collector.j * 70;
            }
            if (s[collector.i * N + collector.j] == '2') {
                s[collector.i * N + collector.j] = '0';
                Dispatcher::apples++;
            }
        }
    }

    // Сканирование клеток от конечной позиции
    Dispatcher::addCoordinates(collector.i * N + collector.j, s[collector.i * N + collector.j]);
    Dispatcher::addCoordinates((collector.i - 1) * N + collector.j, s[(collector.i - 1) * N + collector.j]);
    Dispatcher::addCoordinates((collector.i + 1) * N + collector.j, s[(collector.i + 1) * N + collector.j]);
    Dispatcher::addCoordinates(collector.i * N + (collector.j - 1), s[collector.i * N + (collector.j - 1)]);
    Dispatcher::addCoordinates(collector.i * N + (collector.j + 1), s[collector.i * N + (collector.j + 1)]);
}

void GraphicGame::start(int N) {
    View view, view1;
    int width = 910, height = 910, w = 70;
    RenderWindow app(VideoMode(width, height), "Robots");

    std::ifstream in;
    in.open("C:\\Users\\sofya\\Desktop\\map.txt");
    std::string s = "";

    if(in.is_open()) getline(in, s);
    in.close();

    float heroteleporttimer = 0;
    float heroteleporttimer1 = 0;
    Clock clock;

    Textures empty("empty.png", 70, 70);
    Textures rock("rock.png", 70, 70);
    Textures apple("apple.png", 70, 70);
    Textures bomb("bomb.png", 70, 70);

    Font font;
    font.loadFromFile(R"(C:\Users\sofya\CLionProjects\lab3\Fonts\Roboto-Bold.ttf)");
    Text text("", font, 20);
    text.setFillColor(Color(216, 120, 120));

    view.reset(FloatRect(0, 0, 910, 910));

    Collector collector = Collector();
    collector.sprite.setPosition(collector.x, collector.y);
    Dispatcher::addCollector(Dispatcher::numberOfCol, collector);
    Dispatcher::addCoordinates(collector.i * N + collector.j, s[collector.i * N + collector.j]);

    std::cout << "Collector " << Dispatcher::numberOfCol << " was added" << std::endl;
    std::cout << "Collector " << Dispatcher::numberOfCol << " has " << Collector::mode << " mode"<< std::endl;
    std::cout <<std::endl;

    Textures menu("menu.png", 154, 83);
    menu.sprite.setPosition(0, 0);
    Textures menu2("menu2.png", 170, 83);
    menu2.sprite.setPosition(690, 0);
    view1.reset(FloatRect(0, 0, 840, 840));


    while (app.isOpen()) {
        Event e{};
      while (app.pollEvent(e)) {
            if (e.type == Event::Closed)
                app.close();
        }
        app.clear(Color::White);

        for (size_t i = Dispatcher::collectors[Dispatcher::collectorId].i - 7; i < Dispatcher::collectors[Dispatcher::collectorId].i + 7; ++i) {
            for (size_t j = Dispatcher::collectors[Dispatcher::collectorId].j - 7; j < Dispatcher::collectors[Dispatcher::collectorId].j + 7; ++j) {
                if (s[i * N + j] == '0') {
                    empty.sprite.setTextureRect(IntRect(0, 0, w, w));
                    empty.sprite.setPosition(i * w, j * w);
                    app.draw(empty.sprite);
                }
                if (s[i * N + j] == '1') {
                    rock.sprite.setTextureRect(IntRect(0, 0, w, w));
                    rock.sprite.setPosition(i * w, j * w);
                    app.draw(rock.sprite);
                }
                if (s[i * N + j] == '2') {
                    apple.sprite.setTextureRect(IntRect(0, 0, w, w));
                    apple.sprite.setPosition(i * w, j * w);
                    app.draw(apple.sprite);
                }
                if (s[i * N + j] == '3') {
                    bomb.sprite.setTextureRect(IntRect(0, 0, w, w));
                    bomb.sprite.setPosition(i * w, j * w);
                    app.draw(bomb.sprite);
                }
            }
        }
        view.setCenter(Dispatcher::collectors[Dispatcher::collectorId].sprite.getPosition().x,
                       Dispatcher::collectors[Dispatcher::collectorId].sprite.getPosition().y);

        if(e.type == Event::KeyPressed)
            MoveKey(s, e, Dispatcher::collectors[Dispatcher::collectorId], N, view);

        int menuNum = 0;
        if (IntRect(0, 0, 154, 83).contains(Mouse::getPosition(app)))
            menuNum = 1;

        if (Mouse::isButtonPressed(Mouse::Left))
            if (menuNum == 1) {
                app.setVisible(false);
                Menu menu1;
                menu1.start(app, N, s);
                app.setVisible(true);
            }

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;
        heroteleporttimer += time;
        heroteleporttimer1 += time;

        if (heroteleporttimer > 220 && Dispatcher::automode == true) {
            heroteleporttimer = 0;
            for (size_t i = 1; i < 1000; ++i) {
                if (Dispatcher::sappers[i].sapautomode != 0 && Dispatcher::sappers[i].it1 != Dispatcher::scannedmap.end()) {
                    AutoMode::startSap(s, app, i, Dispatcher::sappers[i].it1, N);
                    Dispatcher::sappers[i].it1++;
                    Dispatcher::automode = true;
                    Dispatcher::sappers[i].wrongCoord = true;
                }
                else if (Dispatcher::sappers[i].it1 == Dispatcher::scannedmap.end()) {
                    Dispatcher::sappers[i].it1 = Dispatcher::scannedmap.begin();
                    Dispatcher::sappers[i].sapautomode = false;
                }
            }
        }

        if (heroteleporttimer1 > 240 && Dispatcher::automode == true) {
            heroteleporttimer1 = 0;
            for(size_t i = 1; i < 1000; ++i) {
                if (Dispatcher::collectors[i].colautomode != 0 && Dispatcher::collectors[i].it != Dispatcher::scannedmap.end()) {
                    Dispatcher::automode = true;
                    AutoMode::startCol(s, app, i, Dispatcher::collectors[i].it, N);
                    Dispatcher::collectors[i].it++;
                }
                else if(Dispatcher::collectors[i].it == Dispatcher::scannedmap.end()){
                    Dispatcher::collectors[i].it = Dispatcher::scannedmap.begin();
                    Dispatcher::collectors[i].colautomode = false;
                    Dispatcher::automode = false;
                }
            }
        }

        app.setView(view1);
        app.draw(menu.sprite);
        app.draw(menu2.sprite);

        std::ostringstream Score;
        Score << Dispatcher::apples;
        text.setString("APLLES\n" + Score.str());
        text.setPosition(720, 20);
        app.draw(text);
        app.setView(view);

        for (size_t i = 1; i <= 1000; i++) {
            if(Dispatcher::sappers[i].exist == true) {
                app.draw(Dispatcher::sappers[i].sprite);
            }
        }

        for (size_t i = 1; i <= 1000; i++) {
            if(Dispatcher::collectors.count(i) != 0)
                app.draw(Dispatcher::collectors[i].sprite);
        }

        app.display();
    }
}


