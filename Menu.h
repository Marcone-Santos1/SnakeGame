#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(sf::RenderWindow& window);
    void show();

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text title;
    sf::Text startButton;
    sf::Text quitButton;

    void handleInput();
    void draw();
};

#endif // MENU_H