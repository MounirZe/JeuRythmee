#ifndef __NOTE__
#define __NOTE__
#include "TypeNote.h"
#include <SFML/Graphics.hpp>

class Note : public sf::CircleShape // Zemmiri
{

private:
	TypeNote typeNote_; // Represente le type de note
	bool played_; // variable binaire qui indique si la note a deja été jouée ou non 
public:
	/**
	Constructeur de Note
	@param typeNote Represente le type de Note (Bleue ou Rouge)
	@param x Position x de Note, par défaut = 0
	@param y Position y de Note, par défaut = 250
	**/
	Note(TypeNoteEnum typeNote, float x = 0, float y = 250);
	/**
	Met à jour la position de la note
	@param speed Vitesse de la note
	**/
	void UpdatePosition(float speed);

	/**
	Retourne le TypeNote de Note
	@return TypeNote represente le type de la Note
	**/
	inline TypeNote getTypeNote() const { return this->typeNote_; }

	/**
	Indique si la note a été jouée
	@return bool True si la note a été jouée
	**/
	inline bool isPlayed() const { return played_; }

	/**
	Defini si la note a été jouée
	@param state True si la note a été jouée, False sinon
	**/
	inline void setPlayed(bool state) { played_ = state; }

};
#endif 