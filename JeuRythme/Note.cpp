#include "Note.h"

Note::Note(TypeNoteEnum typeNote, float x, float y) : typeNote_(typeNote)
{
	this->setPosition(x, y);
	this->setRadius(10);
	this->setFillColor(this->typeNote_.getCouleur());
}

void Note::UpdatePosition(float speed)
{
	sf::Vector2f movement(-speed, 0);
	this->move(movement);
}