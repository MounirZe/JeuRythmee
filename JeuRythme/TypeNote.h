#ifndef __TYPENOTE__
#define __TYPENOTE__

#include <list>
#include <SFML/Graphics.hpp>

using namespace std;

enum TypeNoteEnum {
	Rouge, Bleue
};

class TypeNote // Zemmiri
{
private:
	sf::Color couleur_;
	list < sf::Keyboard::Key > toucheClavier_;
	TypeNoteEnum enumerateur_;
public:
	TypeNote(TypeNoteEnum enumerateur);
	TypeNote() {};
	inline sf::Color const getCouleur() { return couleur_; }
	inline list < sf::Keyboard::Key > const getKeys() { return toucheClavier_; }


};

#endif