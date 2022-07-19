#include "AutoNMode.h"
#include <vector>


void AutoNMode::start(int N, std::string& s, Collector& collector, RenderWindow &app, RenderWindow &new_app, int numSteps) {
    int count = 0;

    for (int i = 1; i <= numSteps; ++i) {
        std::vector<int> array;
        if ((s[(collector.i - 1) * N + collector.j] == '0' || s[(collector.i - 1) * N + collector.j] == '2')
            && collector.collMap.count((collector.i - 1) * N + collector.j) != 1) //Влево
            array.push_back(0);

        if ((s[(collector.i + 1) * N + collector.j] == '0' || s[(collector.i + 1) * N + collector.j] == '2')
            && collector.collMap.count((collector.i + 1) * N + collector.j) != 1) //Вправо
            array.push_back(1);

        if ((s[collector.i * N + (collector.j - 1)] == '0' || s[collector.i * N + (collector.j - 1)] == '2')
            && collector.collMap.count(collector.i * N + (collector.j - 1)) != 1) //Вверх
            array.push_back(2);

        if ((s[collector.i * N + (collector.j + 1)] == '0' || s[collector.i * N + (collector.j + 1)] == '2')
            && collector.collMap.count(collector.i * N + (collector.j + 1)) != 1) //Вниз
            array.push_back(3);

        if(array.size() == 0) // Если нет новых клеток для сканирования
            break;

        // Сканирование клеток на исходной позиции
        Dispatcher::addCoordinates(collector.i * N + collector.j, s[collector.i * N + collector.j]);
        collector.addCoordinates(collector.i * N + collector.j, s[collector.i * N + collector.j]);

        Dispatcher::addCoordinates((collector.i - 1) * N + collector.j, s[(collector.i - 1) * N + collector.j]);
        Dispatcher::addCoordinates((collector.i + 1) * N + collector.j, s[(collector.i + 1) * N + collector.j]);
        Dispatcher::addCoordinates(collector.i * N + (collector.j - 1), s[collector.i * N + (collector.j - 1)]);
        Dispatcher::addCoordinates(collector.i * N + (collector.j + 1), s[collector.i * N + (collector.j + 1)]);

        int step = rand() % array.size(); // Выбор индекса
        switch (array[step]) {
            case 0:
                count++;
                collector.addCoordinates((collector.i - 1) * N + collector.j, s[(collector.i - 1) * N + collector.j]);
                collector.sprite.move(-70, 0);
                app.draw(collector.sprite);
                collector.i--;

                break;
            case 1:
                count++;
                collector.addCoordinates((collector.i + 1) * N + collector.j, s[(collector.i + 1) * N + collector.j]);
                collector.sprite.move(70, 0);
                app.draw(collector.sprite);
                collector.i++;
                break;
            case 2:
                count++;
                collector.addCoordinates(collector.i * N + (collector.j - 1), s[collector.i * N + (collector.j - 1)]);
                collector.sprite.move(0, -70);
                app.draw(collector.sprite);
                collector.j--;
                break;
            case 3:
                count++;
                collector.addCoordinates(collector.i * N + (collector.j + 1), s[collector.i * N + (collector.j + 1)]);
                collector.sprite.move(0, 70);
                app.draw(collector.sprite);
                collector.j++;
                break;
            default:
                break;
        }
    }
    // Сканирование клеток на конечной позиции
    Dispatcher::addCoordinates(collector.i * N + collector.j, s[collector.i * N + collector.j]);
    Dispatcher::addCoordinates((collector.i - 1) * N + collector.j, s[(collector.i - 1) * N + collector.j]);
    Dispatcher::addCoordinates((collector.i + 1) * N + collector.j, s[(collector.i + 1) * N + collector.j]);
    Dispatcher::addCoordinates(collector.i * N + (collector.j - 1), s[collector.i * N + (collector.j - 1)]);
    Dispatcher::addCoordinates(collector.i * N + (collector.j + 1), s[collector.i * N + (collector.j + 1)]);

    std::cout << count << " cells were scanned" << std::endl;
}
