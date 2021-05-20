#ifndef __MENU__
#define __MENU__
#pragma once
#include <SFML/Graphics.hpp>

class Menu {  // Faure
public:
	sf::RenderWindow *renderWindow_;
	sf::Font font;
	sf::Text text[5];
	sf::RectangleShape rectangle[4];
public:
	Menu(float width = 500, float height = 500);
	~Menu();
	void draw(sf::RenderWindow &window);
};
#endif
