#ifndef __TYPENOTE__
#define __TYPENOTE__
// Zemmiri
#include <list>
#include <SFML/Graphics.hpp>

using namespace std;
// Enumerateur qui represente les differents type de Note
enum TypeNoteEnum { 
	Rouge, Bleue, Orange
};

class TypeNote 
{
private:
	sf::Color couleur_; // Couleur du type de note
	list < sf::Keyboard::Key > toucheClavier_; // Liste des touches de clavier pour jouer la note
public:
	/**
Constructeur de TypeNote
@param enumerateur Enumerateur qui represente le type de note
**/
	TypeNote(TypeNoteEnum enumerateur);
	/**
Retourne la couleur de TypeNote
@return Couleur de TypeNote
**/
	inline sf::Color const getCouleur() { return couleur_; }
	/**
Retourne la liste des touches pour jouer la note
@return Liste des touches
**/
	inline list < sf::Keyboard::Key > const getKeys() { return toucheClavier_; }
};
#endif