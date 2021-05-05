#include <SFML/Graphics.hpp>
#include "Note.h"
#include "Musique.h"
#include <iostream>
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Osu! Wish");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        // error...
    }
    
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(150, 0)),
        sf::Vertex(sf::Vector2f(150, 500))
    };


    sf::CircleShape shape_(100);
    shape_.setFillColor(sf::Color::Green);
    shape_.setPosition(50, 50);
    Musique mamusique(window);

    sf::Text score;
	sf::Text com;
	com.setCharacterSize(40);
	com.setFillColor(sf::Color::White);
	com.setFont(font);
	com.setOutlineColor(sf::Color::Red);
	com.setOutlineThickness(4);
	com.setPosition(300, 100);
    score.setCharacterSize(20);
    score.setFillColor(sf::Color::Red);
    score.setFont(font); // font is a sf::Font

    mamusique.genererMusique();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed) {
                mamusique.evenementTouche(event);
            }

        }

        window.clear();


        mamusique.updateMusique();

        score.setString(std::to_string(mamusique.getScore()));
		com.setString(mamusique.getCom());
        window.draw(score);
		window.draw(com);
        window.draw(line, 2, sf::Lines);
        window.display();

    }

    return 0;
}