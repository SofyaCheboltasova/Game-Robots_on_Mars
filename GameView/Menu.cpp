#include "Menu.h"
#include <string>
using namespace sf;
using namespace std;

bool flag = false;
void fixCoordinates(std::string &s, int N, int idx) {
    for(auto& i : Dispatcher::scannedmap) { // Сапер встает на отсканированную клетку
        if(i.second == '3') {
            flag = true;
            Dispatcher::sappers[idx].i = i.first / N;
            Dispatcher::sappers[idx].j = i.first % N;
            Dispatcher::sappers[idx].x = i.first / N * 70;
            Dispatcher::sappers[idx].y = i.first % N * 70;

            s[Dispatcher::sappers[idx].i * N + Dispatcher::sappers[idx].j] = '0';
            Dispatcher::scannedmap[Dispatcher::sappers[idx].i * N + Dispatcher::sappers[idx].j] = '0';

            Dispatcher::sappers[idx].lastBomb = Dispatcher::sappers[idx].i * N + Dispatcher::sappers[idx].j;

            Dispatcher::sappers[idx].sprite.setPosition(Dispatcher::sappers[idx].x, Dispatcher::sappers[idx].y); //Ставим сапера
            break;
        }
    }

    for(auto& i : Dispatcher::scannedmap){
        if(flag == false && i.second == '0') {
            Dispatcher::sappers[idx].i = i.first / N;
            Dispatcher::sappers[idx].j = i.first % N;
            Dispatcher::sappers[idx].x = i.first / N * 70;
            Dispatcher::sappers[idx].y = i.first % N * 70;

            Dispatcher::sappers[idx].sprite.setPosition(Dispatcher::sappers[idx].x, Dispatcher::sappers[idx].y);
            break;
        }
    }
}

void Menu::start(RenderWindow &app, int N, std::string& s) {
    int width = 910, height = 910;
    RenderWindow new_app(VideoMode(width, height), "Menu");
    View view1;
    Textures sapperb("sapper.png", 206, 107);
    Textures collectorb("collector.png", 206, 107);
    Textures mode("set_mode.png", 206, 107);
    Textures manual("Group 27.png", 221, 80);
    Textures scan("Group 29.png", 221, 80);
    Textures automode("Group 30.png", 221, 80);
    Textures sap_on("sapper_on.png", 221, 80);
    Textures sap_off("sapper_off.png", 221, 80);
    Textures new_col("new_collector.png", 221, 80);
    Textures backofbuttons("Background.png", 910, 910);

    view1.reset(FloatRect(0, 0, 910, 910));

    collectorb.sprite.setPosition(40, 220);
    new_col.sprite.setPosition(33, 370);
    sapperb.sprite.setPosition(352, 220);
    sap_on.sprite.setPosition(345, 370);
    sap_off.sprite.setPosition(345, 500);
    mode.sprite.setPosition(664, 220);
    manual.sprite.setPosition(657, 370);
    scan.sprite.setPosition(657, 500);
    automode.sprite.setPosition(657, 630);
    backofbuttons.sprite.setPosition(0, 0);

    while(new_app.isOpen()) {
        Event e{};
        while (new_app.pollEvent(e)) {
            if (e.type == Event::Closed)
                new_app.close();
        }
        new_app.clear(Color::White);

        int menuNum = 0;

        if (IntRect(33, 370, 221, 80).contains(Mouse::getPosition(new_app)))  // New col
            menuNum = 1;

        if (IntRect(345, 370, 221, 80).contains(Mouse::getPosition(new_app))) // Sap on
            menuNum = 2;

        if (IntRect(352, 500, 221, 80).contains(Mouse::getPosition(new_app)))  // Sap off
            menuNum = 3;

        if (IntRect(657, 370, 221, 80).contains(Mouse::getPosition(new_app))) // manual
            menuNum = 4;

        if (IntRect(657, 500, 221, 80).contains(Mouse::getPosition(new_app))) // scan N
            menuNum = 5;

        if (IntRect(657, 630, 221, 80).contains(Mouse::getPosition(new_app))) // auto
            menuNum = 6;


        if (Mouse::isButtonPressed(Mouse::Left)) {
            if(menuNum == 1) {
                Collector collector = Collector();
                Dispatcher::addCollector(Dispatcher::numberOfCol, collector);
                Dispatcher::numberOfCol++;

                for(auto& i : Dispatcher::scannedmap){
                    if(i.second == '0') {
                        Dispatcher::collectors[Dispatcher::numberOfCol].i = i.first / N;
                        Dispatcher::collectors[Dispatcher::numberOfCol].j = i.first % N;
                        Dispatcher::collectors[Dispatcher::numberOfCol].x = i.first / N * 70;
                        Dispatcher::collectors[Dispatcher::numberOfCol].y = i.first % N * 70;

                        Dispatcher::collectors[Dispatcher::numberOfCol].lastCell = Dispatcher::collectors[Dispatcher::numberOfCol].i * N +
                                                                                   Dispatcher::collectors[Dispatcher::numberOfCol].j ;
                        Dispatcher::collectors[Dispatcher::numberOfCol].sprite.setPosition(Dispatcher::collectors[Dispatcher::numberOfCol].x,
                                                                                           Dispatcher::collectors[Dispatcher::numberOfCol].y); //Ставим робота
                        break;
                    }
                }
                std::cout << "Collector " << Dispatcher::numberOfCol << " was added" << std::endl;
                std::cout << "Collector " << Dispatcher::numberOfCol << " has no mode"<< std::endl;
                std::cout << std::endl;

                new_app.close();
            }

            if(menuNum == 2) {
                Dispatcher::numberOfSap++;
                int NumSap = -1;
                Sapper sapper = Sapper();
                for(size_t i = 1; i <= Dispatcher::numberOfSap; ++i) {
                    if(Dispatcher::sappers[i].exist == false) {
                        Dispatcher::sappers[i].exist = true;
                        Dispatcher::addSapper(i, sapper);
                        NumSap = i;

                        fixCoordinates(s, N, i);
                        break;
                    }
                }

                if(NumSap == -1) {
                    fixCoordinates(s, N, Dispatcher::numberOfSap);
                    Dispatcher::addSapper(Dispatcher::numberOfSap, sapper);
                    std::cout << "Sapper " << Dispatcher::numberOfSap << " was added" << std::endl;
                }
                else
                    std::cout << "Sapper " << NumSap << " was added" << std::endl;
                std::cout << std::endl;
                new_app.close();
            }

            if(menuNum == 3) {
                int w = 357, h = 73;
                RenderWindow textbox(VideoMode(w, h), "Sapper off");
                Textures choose_id("id.png", 357, 73);
                choose_id.sprite.setPosition(0, 0);

                string enterId;
                Font font;
                font.loadFromFile("C:\\Users\\sofya\\AppData\\Local\\Microsoft\\Windows\\Fonts\\Roboto-Regular.ttf");
                Text playerText("", font, 30);
                playerText.setFillColor(sf::Color::Black);
                playerText.setPosition(80, 15);
                while(textbox.isOpen()) {
                    Event e{};
                    while (textbox.pollEvent(e)) {
                        if (e.type == Event::Closed || e.key.code == Keyboard::Return) {
                            textbox.close();
                            new_app.close();
                        }
                        if (e.type == sf::Event::TextEntered) {
                            if (e.text.unicode == '\b') {
                                enterId.erase(enterId.size() - 1, 1);
                            } else
                                enterId += e.text.unicode;
                            playerText.setString(enterId);
                        }
                    }

                    if(atoi(enterId.c_str()) != 0) {
                        Dispatcher::sapperId = atoi(enterId.c_str()); // Ввод ID сапера
                        Dispatcher::sappers.erase(Dispatcher::sapperId);
                        Dispatcher::sappers[Dispatcher::sapperId].exist = false;
                        Dispatcher::numberOfSap--;
                        new_app.close();
                        return;
                    }
                    textbox.draw(choose_id.sprite);
                    textbox.draw(playerText);
                    textbox.display();
                }
                std::cout << "Sapper " << Dispatcher::sapperId << " was deleted" << std::endl;
                std::cout << std::endl;
            }

            if(menuNum == 4 || menuNum == 6) {
                int w = 357, h = 73;
                RenderWindow textbox(VideoMode(w, h), "Mode");
                Textures choose_id("id.png", 357, 73);
                choose_id.sprite.setPosition(0, 0);

                string enterId;
                Font font;
                font.loadFromFile("C:\\Users\\sofya\\AppData\\Local\\Microsoft\\Windows\\Fonts\\Roboto-Regular.ttf");
                Text playerText("", font, 30);
                playerText.setFillColor(sf::Color::Black);
                playerText.setPosition(80, 15);

                while(textbox.isOpen()) {
                    Event e{};
                    while (textbox.pollEvent(e)) {
                        if (e.type == Event::Closed || e.key.code == Keyboard::Return) {
                            textbox.close();
                            new_app.close();
                        }
                        if (e.type == sf::Event::TextEntered) {
                            if (e.text.unicode == '\b') { // backspace
                                enterId.erase(enterId.size() - 1, 1);
                            }
                            else
                                enterId += e.text.unicode;
                            playerText.setString(enterId);
                        }
                    }
                    if(atoi(enterId.c_str()) > 0) {
                        if (menuNum == 4) {
                            Dispatcher::collectorId = atoi(enterId.c_str()); // Ввод ID для <collector manual mode>
                            Collector::mode = "manual";
                            Dispatcher::automode = false;
                        }

                        if (menuNum == 6) {
                            Collector::mode = "auto";
                            Dispatcher::automode = true;
                            Dispatcher::autoId = atoi(enterId.c_str()); // Ввод ID для <collector auto mode>
                            Dispatcher::collectors[Dispatcher::autoId].colautomode = 1;

                            if(Dispatcher::autoId <= Dispatcher::numberOfSap) {
                                Dispatcher::sappers[Dispatcher::autoId].sapautomode = 1;
                            }

                            if(Dispatcher::autoId > Dispatcher::numberOfSap){
                                Sapper sapper = Sapper();
                                Dispatcher::numberOfSap += 1;
                                Dispatcher::addSapper(Dispatcher::autoId, sapper);

                                Dispatcher::sappers[Dispatcher::autoId].sapautomode = 1;
                                Dispatcher::sappers[Dispatcher::autoId].lastBomb = Dispatcher::sappers[Dispatcher::autoId].i * N +
                                                                                   Dispatcher::sappers[Dispatcher::autoId].j;
                            }
                        }
                    }
                    textbox.draw(choose_id.sprite);
                    textbox.draw(playerText);
                    textbox.display();
                }
                if(menuNum == 4 && atoi(enterId.c_str()) != 0) {
                    std::cout << "Collector's " << Dispatcher::collectorId << " mode was changed to " << Collector::mode
                              << std::endl;
                    std::cout << std::endl;
                }
                if(menuNum == 6 && atoi(enterId.c_str()) != 0) {
                    std::cout << "Collector's " << Dispatcher::autoId << " mode was changed to " << Collector::mode
                              << std::endl;
                    std::cout << std::endl;
                }
            }

            if(menuNum == 5) {
                int w = 357, h = 73, collectorId;
                RenderWindow textbox(VideoMode(w, h), "Mode");
                Textures choose_id("id.png", 357, 73);
                choose_id.sprite.setPosition(0, 0);

                std::string enterId;
                Font font;
                font.loadFromFile("C:\\Users\\sofya\\AppData\\Local\\Microsoft\\Windows\\Fonts\\Roboto-Regular.ttf");
                Text playerText("", font, 30);
                playerText.setFillColor(sf::Color::Black);
                playerText.setPosition(80, 15);

                while(textbox.isOpen()) {
                    Event e{};
                    while (textbox.pollEvent(e)){
                        if (e.type == Event::Closed || e.key.code == Keyboard::Return) {
                            int it = 0; std::string s1 = ""; std::string s2 = "";
                            while(enterId[it] != ' ') {
                                s1 += enterId[it];
                                it++;
                            }
                            it++;
                            while(it < enterId.size()) {
                                s2 += enterId[it];
                                it++;
                            }

                            collectorId = atoi(s1.c_str());
                            Dispatcher::numSteps = atoi(s2.c_str());

                            AutoNMode::start(N, s, Dispatcher::collectors[collectorId], app, new_app, Dispatcher::numSteps);

                            textbox.close();
                            new_app.close();
                        }
                        if (e.type == sf::Event::TextEntered) {
                            if (e.text.unicode == '\b') { //backspace
                                enterId.erase(enterId.size() - 1, 1);
                            }
                            else
                                enterId += e.text.unicode;
                            playerText.setString(enterId);
                        }
                    }
                    textbox.draw(choose_id.sprite);
                    textbox.draw(playerText);
                    textbox.display();
                }
                std::cout << "Collector's " << collectorId << " mode was changes to Scan " << Dispatcher::numSteps<< " cells" << std::endl;
                if(collectorId == Dispatcher::collectorId)
                    std::cout << "Collector " << collectorId << " has manual mode"<< std::endl;
                else
                    std::cout << "Collector " << collectorId << " has no mode"<< std::endl;
                std::cout << std::endl;
            }
        }

        new_app.setView(view1);
        new_app.draw(backofbuttons.sprite);
        new_app.draw(sapperb.sprite);
        new_app.draw(collectorb.sprite);
        new_app.draw(mode.sprite);
        new_app.draw(sap_on.sprite);
        new_app.draw(sap_off.sprite);
        new_app.draw(new_col.sprite);
        new_app.draw(manual.sprite);
        new_app.draw(scan.sprite);
        new_app.draw(automode.sprite);
        new_app.display();
    }
}
