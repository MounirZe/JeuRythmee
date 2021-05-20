#include "menu.h"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		// handle error
	}
	text[0].setFont(font);
	text[0].setFillColor(sf::Color::White);
	text[0].setString("GAME MENU");
	text[0].setPosition(100, 100);
	text[0].setCharacterSize(40);
	text[0].setOutlineColor(sf::Color::Red);
	text[0].setOutlineThickness(4);

	text[1].setFont(font);
	text[1].setFillColor(sf::Color::White);
	text[1].setString("PLAY");
	text[1].setPosition(0, 200);
	text[1].setCharacterSize(20);
	text[1].setOutlineColor(sf::Color::Blue);
	text[1].setOutlineThickness(4);

	text[2].setFont(font);
	text[2].setFillColor(sf::Color::White);
	text[2].setString("EASY");
	text[2].setPosition(0, 300);
	text[2].setCharacterSize(20);
	text[2].setOutlineColor(sf::Color::Green);
	text[2].setOutlineThickness(4);

	text[3].setFont(font);
	text[3].setFillColor(sf::Color::White);
	text[3].setString("MEDIUM");
	text[3].setPosition(85, 300);
	text[3].setCharacterSize(20);
	text[3].setOutlineColor(sf::Color::Color(255, 124, 0));
	text[3].setOutlineThickness(4);

	text[4].setFont(font);
	text[4].setFillColor(sf::Color::White);
	text[4].setString("HARD");
	text[4].setPosition(200, 300);
	text[4].setCharacterSize(20);
	text[4].setOutlineColor(sf::Color::Red);
	text[4].setOutlineThickness(4);

	rectangle[0].setSize(sf::Vector2f(70, 50));
	rectangle[0].setPosition(0, 190);

	rectangle[1].setSize(sf::Vector2f(70, 50));
	rectangle[1].setPosition(0, 190);

	rectangle[2].setSize(sf::Vector2f(90, 50));
	rectangle[2].setPosition(80, 290);

	rectangle[3].setSize(sf::Vector2f(70, 50));
	rectangle[3].setPosition(200, 290);

}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow & window)
{
	for (int i = 0; i < 5; i++)
	{
		window.draw(text[i]);
	}
}
