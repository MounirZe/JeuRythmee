#ifndef __NOTE__
#define __NOTE__
#include "TypeNote.h"
#include <SFML/Graphics.hpp>

class Note
{

private:
	TypeNote typeNote_;
	sf::CircleShape shape_;
public:
	Note(TypeNoteEnum typeNote, float x = 0, float y =250);
	void UpdatePosition();
	inline sf::CircleShape getShape() { return this->shape_; }
};
#endif
