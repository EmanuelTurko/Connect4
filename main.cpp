#include <SFML/Graphics.hpp>

#include "Game.h"

int main() {

    Game newGame;
    newGame.Run();

   /* sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Test");
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
        }
        window.clear();
        window.display();
    }*/
}
