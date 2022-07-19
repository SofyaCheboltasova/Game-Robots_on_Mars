cmake_minimum_required(VERSION 3.17)
project(lab3)

set(CMAKE_CXX_STANDARD 20)


set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)


add_executable(lab3 main.cpp Robot/Textures.cpp Robot/Textures.h Robot/Collector.cpp Robot/Collector.h Robot/Sapper.h Robot/Sapper.cpp Dispatcher.cpp Dispatcher.h GameView/AutoMode.cpp GameView/AutoMode.h GameView/AutoNMode.cpp GameView/AutoNMode.h GameView/GraphicView.cpp GameView/GraphicView.h GameView/Menu.cpp GameView/Menu.h)
target_link_libraries(lab3 sfml-graphics)

