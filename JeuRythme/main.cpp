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
	// Initialisation des variables de gestion du jeu
	bool gamePause = false;
	bool gameMenu = true;

	// Initialisation de la fenetre de jeu de taille 500 500
	sf::RenderWindow window(sf::VideoMode(500, 500), "Osu! Wish", sf::Style::Close);

	// Initialisation et chargement de la police
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}

	// Declaration d'une ligne pour que le joueur puisse se situer
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(150, 0)),
		sf::Vertex(sf::Vector2f(150, 500))
	};
	// Initilisation du menu et de la classe musique
	Menu menu(window,font);

	Musique mamusique(window,font);


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

	// Declaration et initalisation des textes de l'ecran de pause
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

	// Declaration et chargement de la musique (audio)
	sf::Music musique;
	musique.openFromFile("musique.wav");



	while (window.isOpen()) // Boucle tant que la fenetre n'est pas fermée
	{
		sf::Event event;
		// Gestion des differents evenements
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
				if (menu.rectangle[0].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					gameMenu = false;
					musique.play();
				}
				if (menu.rectangle[1].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					//action quand clique sur difficulte easy 
					mamusique.setDifficulty(1);
				}
				if (menu.rectangle[2].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					//action quand clique sur difficulte medium
					mamusique.setDifficulty(2);
				}
				if (menu.rectangle[3].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					//action quand clique sur difficulte hard
					mamusique.setDifficulty(3);
				}
			}
		}
		window.clear(); // Clear de la fenetre pour dessiner les nouveaux objets sur la fenetre

		if (!gamePause && !gameMenu) // Si le jeu est lancé
		{
			mamusique.updateMusique(); // Mise à jour des differentes notes et indicateurs graphique comme le score
			window.draw(line, 2, sf::Lines); // Dessine la ligne pour se situer 
		}
		else if (gamePause && !gameMenu) // Si le jeu est en pause
		{
			// Dessine les differents text et met la musique en pause
			window.draw(pause);
			window.draw(resume);
			window.draw(exit);
			musique.pause();
		}
		else if (gameMenu) // Si le joueur est sur le menu
		{
			menu.draw(); // Dessine le menu
		}
		window.display(); // Affiche la fenetre mise à jour 

	}

	return 0;
}
