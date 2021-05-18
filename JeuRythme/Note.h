#ifndef __NOTE__
#define __NOTE__
#include "TypeNote.h"
#include <SFML/Graphics.hpp>

class Note // Zemmiri/Faure
{

private:
	TypeNote typeNote_; // note rouge ou bleu 
	sf::CircleShape shape_; // forme des notes 
	bool played_; // variable binaire qui indique si la note a deja été jouée ou non 
public:
	Note(TypeNoteEnum typeNote, float x = 0, float y =250);
	void UpdatePosition();

	inline TypeNote getTypeNote() const { return this->typeNote_; }

	inline sf::CircleShape getShape() const { return this->shape_; }

	inline bool isPlayed() const { return played_; }
	inline void setPlayed(bool state) { played_ = state; }
	inline void setColor(sf::Color color) { this->shape_.setFillColor(color); }

};
#endif 
// com 
