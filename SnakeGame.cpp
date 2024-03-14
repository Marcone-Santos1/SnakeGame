//
// Created by ms580 on 14/03/2024.
//

#include "SnakeGame.h"

const int CELL_SIZE = 20;
const int GRID_WIDTH = 30;
const int GRID_HEIGHT = 20;
const int WINDOW_WIDTH = CELL_SIZE * GRID_WIDTH;
const int WINDOW_HEIGHT = CELL_SIZE * GRID_HEIGHT;

SnakeGame::SnakeGame() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game") {
    snake.push_front({GRID_WIDTH / 2, GRID_HEIGHT / 2});
    spawnFruit();
}

void SnakeGame::run() {
    sf::Clock clock;
    float deltaTime = 0.0f;
    while (window.isOpen()) {
        processEvents();
        deltaTime = clock.restart().asSeconds();
        update(deltaTime);
        render();
    }
}

void SnakeGame::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case (sf::Keyboard::W):
                    if (direction != Direction::Down)
                        direction = Direction::Up;
                    break;
                case sf::Keyboard::S:
                    if (direction != Direction::Up)
                        direction = Direction::Down;
                    break;
                case sf::Keyboard::A:
                    if (direction != Direction::Right)
                        direction = Direction::Left;
                    break;
                case sf::Keyboard::D:
                    if (direction != Direction::Left)
                        direction = Direction::Right;
                    break;
                default:
                    break;
            }
        }
    }
}

void SnakeGame::update(float deltaTime) {
    static float timer = 0;
    timer += deltaTime;
    if (timer > 0.1f) {
        moveSnake();
        checkCollision();
        timer = 0;
    }
}

void SnakeGame::render() {
    window.clear();

    // Draw Snake
    bool isFirstSegment = true;
    for (const auto& segment : snake) {
        sf::RectangleShape shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        shape.setPosition(segment.x * CELL_SIZE, segment.y * CELL_SIZE);

        if (isFirstSegment) {
            shape.setFillColor(sf::Color::White);
            isFirstSegment = false;
        } else {
            shape.setFillColor(sf::Color::Green);
        }
        window.draw(shape);
    }

    // Draw Fruit
    sf::RectangleShape fruitShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    fruitShape.setPosition(fruit.x * CELL_SIZE, fruit.y * CELL_SIZE);
    fruitShape.setFillColor(sf::Color::Red);
    window.draw(fruitShape);

    window.display();
}

void SnakeGame::moveSnake() {
    SnakeSegment newHead = snake.front();
    switch (direction) {
        case Direction::Up:
            newHead.y--;
            break;
        case Direction::Down:
            newHead.y++;
            break;
        case Direction::Left:
            newHead.x--;
            break;
        case Direction::Right:
            newHead.x++;
            break;
        default:
            break;
    }
    snake.push_front(newHead);
    if (newHead.x == fruit.x && newHead.y == fruit.y) {
        spawnFruit();
    } else {
        snake.pop_back();
    }
}

void SnakeGame::checkCollision() {
    // Check if snake collides with itself
    for (auto it = snake.begin() + 1; it != snake.end(); ++it) {
        if (it->x == snake.front().x && it->y == snake.front().y) {
            window.close();
        }
    }
    // Check if snake collides with walls

    if (snake.front().x < 0)
        snake.front().x = GRID_WIDTH - 1;
    else if (snake.front().x >= GRID_WIDTH)
        snake.front().x = 0;
    if (snake.front().y < 0)
        snake.front().y = GRID_HEIGHT - 1;
    else if (snake.front().y >= GRID_HEIGHT)
        snake.front().y = 0;
}

void SnakeGame::spawnFruit() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> disX(0, GRID_WIDTH - 1);
    static std::uniform_int_distribution<> disY(0, GRID_HEIGHT - 1);

    int x, y;
    do {
        x = disX(gen);
        y = disY(gen);
    } while (isSegmentInSnake(x, y));

    fruit = {x, y};
}

bool SnakeGame::isSegmentInSnake(int x, int y) const {
    for (const auto& segment : snake) {
        if (segment.x == x && segment.y == y) {
            return true;
        }
    }
    return false;
}
