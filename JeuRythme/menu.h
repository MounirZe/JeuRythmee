#ifndef __MENU__
#define __MENU__
#include <SFML/Graphics.hpp>

class Menu {  // Faure
public:
	sf::RenderWindow *renderWindow_;
	sf::Text text[5];
	sf::RectangleShape rectangle[4];
public:
	Menu(sf::RenderWindow& window, sf::Font& font);
	void draw();
};
#endif
