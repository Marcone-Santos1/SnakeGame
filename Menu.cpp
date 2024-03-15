#include "Menu.h"
#include "SnakeGame.h"

Menu::Menu(sf::RenderWindow &window) : window(window) {
    if (!font.loadFromFile("C:\\Arial.ttf")) {
        window.close();
    }

    title.setFont(font);
    title.setString("Snake Game");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
    title.setPosition(window.getSize().x / 2, 50.f);

    startButton.setFont(font);
    startButton.setString("Start");
    startButton.setCharacterSize(30);
    startButton.setFillColor(sf::Color::White);
    startButton.setOrigin(startButton.getLocalBounds().width / 2, startButton.getLocalBounds().height / 2);
    startButton.setPosition(window.getSize().x / 2, 200.f);

    quitButton.setFont(font);
    quitButton.setString("Quit");
    quitButton.setCharacterSize(30);
    quitButton.setFillColor(sf::Color::White);
    quitButton.setOrigin(quitButton.getLocalBounds().width / 2, quitButton.getLocalBounds().height / 2);
    quitButton.setPosition(window.getSize().x / 2, 300.f);

}

void Menu::show() {
    while (window.isOpen()) {
        handleInput();
        draw();
    }
}

void Menu::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (startButton.getGlobalBounds().contains(mousePos)) {
                SnakeGame game;
                game.run();

            } else if (quitButton.getGlobalBounds().contains(mousePos)) {
                window.close();
            }
        }
    }
}

void Menu::draw() {
    window.clear();

    window.draw(title);
    window.draw(startButton);
    window.draw(quitButton);

    window.display();
}
