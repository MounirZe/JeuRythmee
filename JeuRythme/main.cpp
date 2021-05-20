#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/AlResource.hpp>
#include <SFML/Audio/SoundStream.hpp>
#include <SFML/Audio/SoundSource.hpp>
#include "Note.h"
#include "menu.h"
#include "Musique.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	int difficulty = 1;
	bool gamePause = false;
	bool gameMenu = true;
	sf::RenderWindow window(sf::VideoMode(500, 500), "Osu! Wish", sf::Style::Close);

	Menu menu();
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

	Musique mamusique(window);


	// Utilisation d'un fichier de config pour charger la musique souhaitée, le fichier de config contient une ligne qui est le chemin de la musique
	string configFileName = "config.txt";
	ifstream configFile;
	configFile.open(configFileName);
	string notePath = "";


	if (configFile.is_open())
	{
		getline(configFile, notePath);
	}
	if (notePath != "") {
		mamusique.genererMusique(notePath);//Chargement de la musique indiquée dans le fichier de config

	}
	else {
		mamusique.genererMusique(); //Musique par défaut 
	}
	sf::CircleShape shape_(100);
	shape_.setFillColor(sf::Color::Green);
	shape_.setPosition(50, 50);

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
			if (!gameMenu && (event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Escape)) {
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
				if (menu.rectangle[1].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					gameMenu = false;
					musique.play();
				}
				if (menu.rectangle[2].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					//action quand clique sur difficulte easy 
					difficulty = 1;
					mamusique.setDifficulty(difficulty);
				}
				if (menu.rectangle[3].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					//action quand clique sur difficulte medium
					difficulty = 2;
					mamusique.setDifficulty(difficulty);
				}
				if (menu.rectangle[3].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					//action quand clique sur difficulte hard
					difficulty = 3;
					mamusique.setDifficulty(difficulty);
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
			menu.draw(window);
		}
		score.setString(std::to_string(mamusique.getScore()));
		retourTiming.setString(mamusique.getRetourTiming());
		window.draw(score);
		window.display();

	}

	return 0;
}
