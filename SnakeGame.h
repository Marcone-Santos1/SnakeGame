//
// Created by ms580 on 14/03/2024.
//

#ifndef SNAKEGAME_SNAKEGAME_H
#define SNAKEGAME_SNAKEGAME_H


#include <SFML/Graphics.hpp>
#include <deque>
#include <random>

struct SnakeSegment {
    int x, y;
};

enum class Direction { None, Up, Down, Left, Right };

class SnakeGame {
public:
    SnakeGame();
    void run();

private:
    sf::RenderWindow window;
    std::deque<SnakeSegment> snake;
    Direction direction = Direction::None;
    SnakeSegment fruit;

    void processEvents();
    void update(float deltaTime);
    void render();
    void moveSnake();
    void checkCollision();
    void spawnFruit();
    bool isSegmentInSnake(int x, int y) const;
};


#endif //SNAKEGAME_SNAKEGAME_H
