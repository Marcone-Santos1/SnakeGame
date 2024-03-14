cmake_minimum_required(VERSION 3.27)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(SnakeGame main.cpp
        SnakeGame.cpp
        SnakeGame.h
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR D:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(D:/SFML/include/SFML)
target_link_libraries(SnakeGame sfml-system sfml-window sfml-graphics sfml-audio)