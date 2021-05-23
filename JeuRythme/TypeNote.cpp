#include "TypeNote.h"


TypeNote::TypeNote(TypeNoteEnum enumerateur) 
{
	switch (enumerateur) { // En fonction de l'enumerateur utilisé dans le constructeur
		case TypeNoteEnum::Rouge:
			this->toucheClavier_.push_back(sf::Keyboard::X); // Ajout des touches pour jouer la note
			this->toucheClavier_.push_back(sf::Keyboard::C);
			this->couleur_ = sf::Color::Red; // Couleur de la note
			break;
		case TypeNoteEnum::Bleue:
			this->toucheClavier_.push_back(sf::Keyboard::W);
			this->toucheClavier_.push_back(sf::Keyboard::V);
			this->couleur_ = sf::Color::Blue;
			break;
		case TypeNoteEnum::Orange:
			this->toucheClavier_.push_back(sf::Keyboard::S);
			this->toucheClavier_.push_back(sf::Keyboard::D);
			this->couleur_ = sf::Color::Color(255, 124, 0);
			break;
		default:
			this->toucheClavier_.push_back(sf::Keyboard::X);
			this->toucheClavier_.push_back(sf::Keyboard::C);
			this->couleur_ = sf::Color::Red;
	}
}
