#include "TypeNote.h"


TypeNote::TypeNote(TypeNoteEnum enumerateur)
{
	switch (enumerateur) {
		case TypeNoteEnum::Rouge:
			this->enumerateur_ = enumerateur;
			this->toucheClavier_.push_back(sf::Keyboard::X);
			this->toucheClavier_.push_back(sf::Keyboard::C);
			this->couleur_ = sf::Color::Red;
			break;
		case TypeNoteEnum::Bleue:
			this->enumerateur_ = enumerateur;
			this->toucheClavier_.push_back(sf::Keyboard::W);
			this->toucheClavier_.push_back(sf::Keyboard::V);
			this->couleur_ = sf::Color::Blue;
			break;
		default:
			this->enumerateur_ = enumerateur;
			this->toucheClavier_.push_back(sf::Keyboard::X);
			this->toucheClavier_.push_back(sf::Keyboard::C);
			this->couleur_ = sf::Color::Red;
	}
}
