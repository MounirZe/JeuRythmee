#ifndef __MENU__
#define __MENU__
#include <SFML/Graphics.hpp>

class Menu {  // Faure
public:
	sf::RenderWindow *renderWindow_; // Fenêtre d'affichage 
	sf::Text text[5]; // Les différents textes affichés dans le menu
	sf::RectangleShape rectangle[4]; // Les différents rectangles servant de hitbox pour les cliques dans le menu 
public:	
	/**
	Constructeur de Menu
	@param window Fenetre où le menu va être affiché
	@param font Police d'écriture utilisée
	**/
	Menu(sf::RenderWindow& window, sf::Font& font); 
	void draw(); // Fonction qui dessine le menu 
};
#endif
