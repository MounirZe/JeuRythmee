#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/AlResource.hpp>
#include <SFML/Audio/SoundStream.hpp>
#include <SFML/Audio/SoundSource.hpp>
#include "Note.h"
#include "Musique.h"
#include <iostream>
using namespace std;

int main()
{
	bool gamePause = false;
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

	sf::Text pause;
	pause.setCharacterSize(40);
	pause.setFillColor(sf::Color::White);
	pause.setOutlineColor(sf::Color::Red);
	pause.setOutlineThickness(4);
	pause.setPosition(100, 100);
	pause.setString("GAME PAUSED");
	pause.setFont(font);

	sf::Text resume;
	resume.setCharacterSize(20);
	resume.setFillColor(sf::Color::White);
	resume.setOutlineColor(sf::Color::Green);
	resume.setOutlineThickness(4);
	resume.setPosition(0, 200);
	resume.setString("PRESS R TO RESUME");
	resume.setFont(font);

	sf::Text exit;
	exit.setCharacterSize(20);
	exit.setFillColor(sf::Color::White);
	exit.setOutlineColor(sf::Color::Red);
	exit.setOutlineThickness(4);
	exit.setPosition(0, 300);
	exit.setString("PRESS SPACE TO EXIT THE GAME");
	exit.setFont(font);

	sf::Music musique; 
	musique.openFromFile("musique.wav");
	musique.play();
    sf::Text score;
	sf::Text com; // Variable de texte pour affichage IU
	com.setCharacterSize(40); // Définition des différents paramètres de com
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
		if ((event.type == sf::Event::KeyReleased) && ( event.key.code == sf::Keyboard::Escape)) {
			cout << "pause" << endl;
			gamePause = true;
		}
		if (gamePause && (event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::R))
		{
			musique.play();
			gamePause = false;
		}
		if (gamePause && (event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Space))
		{
			window.close();
		}
        }

        window.clear();
		if (!gamePause)
		{
			mamusique.updateMusique();
			window.draw(com);
			window.draw(line, 2, sf::Lines);
		}
		else if (gamePause)
		{
			window.draw(pause);
			window.draw(resume);
			window.draw(exit);
			musique.pause();
		}
        score.setString(std::to_string(mamusique.getScore()));
		com.setString(mamusique.getCom());
        window.draw(score);
        window.display();

    }

    return 0;
}
