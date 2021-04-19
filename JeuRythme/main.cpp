#include <SFML/Graphics.hpp>
#include "Note.h"
#include "Musique.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
    Note manote;

    sf::CircleShape shape_(100);
    shape_.setFillColor(sf::Color::Green);
    shape_.setPosition(50, 50);
    Musique mamusique(window);
    mamusique.genererMusique();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        manote.UpdatePosition();

        mamusique.updateMusique();

        window.draw(manote.getShape());
        window.display();

    }

    return 0;
}