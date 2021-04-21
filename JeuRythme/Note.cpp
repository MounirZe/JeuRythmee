#include "Note.h"

Note::Note(TypeNoteEnum typeNote, float x , float y )
{
	this->typeNote_ = TypeNote(typeNote);
	this->shape_.setPosition(x, y);
	this->shape_.setRadius(10);
	this->shape_.setFillColor(this->typeNote_.getCouleur());
}

void Note::UpdatePosition()
{
	sf::Vector2f movement(-0.1f, 0);
	this->shape_.move(movement);
}
