#include "SnakeGame.h"
#include "Menu.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 400), "Snake Menu");
    Menu menu(window);
    menu.show();
    return 0;
}