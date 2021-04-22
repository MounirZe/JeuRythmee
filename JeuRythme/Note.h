#ifndef __NOTE__
#define __NOTE__
#include "TypeNote.h"
#include <SFML/Graphics.hpp>

class Note
{

private:
	TypeNote typeNote_;
	sf::CircleShape shape_;
	bool played_;
public:
	Note(TypeNoteEnum typeNote, float x = 0, float y =250);
	void UpdatePosition();

	inline TypeNote getTypeNote() const { return this->typeNote_; }

	inline sf::CircleShape getShape() const { return this->shape_; }

	inline bool isPlayed() const { return played_; }
	inline void setPlayed(bool state) { played_ = state; }

};
#endif
