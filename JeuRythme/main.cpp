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
	int difficulty = 1;
	bool gamePause = false;
	bool gameMenu = true;
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

	sf::RectangleShape rectangle(sf::Vector2f(70, 50));
	rectangle.setFillColor(sf::Color::Black);
	rectangle.setPosition(0, 190);

	sf::RectangleShape rectangle1(sf::Vector2f(70, 50));
	rectangle1.setFillColor(sf::Color::Black);
	rectangle1.setPosition(0, 290);

	sf::RectangleShape rectangle2(sf::Vector2f(90, 50));
	rectangle2.setFillColor(sf::Color::Black);
	rectangle2.setPosition(80, 290);

	sf::RectangleShape rectangle3(sf::Vector2f(70, 50));
	rectangle3.setFillColor(sf::Color::Black);
	rectangle3.setPosition(200, 290);

	sf::Text pause;
	pause.setCharacterSize(40);
	pause.setFillColor(sf::Color::White);
	pause.setOutlineColor(sf::Color::Red);
	pause.setOutlineThickness(4);
	pause.setPosition(100, 100);
	pause.setString("GAME PAUSED");
	pause.setFont(font);

	sf::Text menu;
	menu.setCharacterSize(40);
	menu.setFillColor(sf::Color::White);
	menu.setOutlineColor(sf::Color::Red);
	menu.setOutlineThickness(4);
	menu.setPosition(100, 100);
	menu.setString("GAME MENU");
	menu.setFont(font);

	sf::Text startGame;
	startGame.setCharacterSize(20);
	startGame.setFillColor(sf::Color::White);
	startGame.setOutlineColor(sf::Color::Blue);
	startGame.setOutlineThickness(4);
	startGame.setPosition(0, 200);
	startGame.setString("START");
	startGame.setFont(font);


	sf::Text diff;
	diff.setCharacterSize(20);
	diff.setFillColor(sf::Color::White);
	diff.setOutlineColor(sf::Color::Green);
	diff.setOutlineThickness(4);
	diff.setPosition(0, 300);
	diff.setString("EASY");
	diff.setFont(font);

	sf::Text diff1;
	diff1.setCharacterSize(20);
	diff1.setFillColor(sf::Color::White);
	diff1.setOutlineColor(sf::Color::Color(255, 124, 0));
	diff1.setOutlineThickness(4);
	diff1.setPosition(85, 300);
	diff1.setString("MEDIUM");
	diff1.setFont(font);

	sf::Text diff2;
	diff2.setCharacterSize(20);
	diff2.setFillColor(sf::Color::White);
	diff2.setOutlineColor(sf::Color::Red);
	diff2.setOutlineThickness(4);
	diff2.setPosition(200, 300);
	diff2.setString("HARD");
	diff2.setFont(font);

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

    sf::Text score;
	sf::Text retourTiming; // Variable de texte pour affichage IU
	retourTiming.setCharacterSize(40); // Définition des différents paramètres de retourTiming
	retourTiming.setFillColor(sf::Color::White);
	retourTiming.setFont(font);
	retourTiming.setOutlineColor(sf::Color::Red);
	retourTiming.setOutlineThickness(4);
	retourTiming.setPosition(300, 100);
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
			if (gameMenu && (event.type == sf::Event::MouseButtonReleased))
			{
				if (rectangle.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					gameMenu = false;
					musique.play();
				}
				if (rectangle1.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					//action quand clique sur difficulte easy 
					difficulty = 1;
				}
				if (rectangle2.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					//action quand clique sur difficulte medium
					difficulty = 2;
				}
				if (rectangle3.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					//action quand clique sur difficulte hard
					difficulty = 3;
				}
			}
        }

        window.clear();
		if (!gamePause && !gameMenu)
		{
			mamusique.updateMusique();
			window.draw(retourTiming);
			window.draw(line, 2, sf::Lines);
		}
		else if (gamePause && !gameMenu)
		{
			window.draw(pause);
			window.draw(resume);
			window.draw(exit);
			musique.pause();
		}
		else if (gameMenu)
		{
			window.draw(rectangle);
			window.draw(rectangle1);
			window.draw(rectangle2);
			window.draw(rectangle3);
			window.draw(menu);
			window.draw(diff);
			window.draw(diff1);
			window.draw(diff2);
			window.draw(startGame);
		}
        score.setString(std::to_string(mamusique.getScore()));
		retourTiming.setString(mamusique.getRetourTiming());
        window.draw(score);
        window.display();

    }

    return 0;
}