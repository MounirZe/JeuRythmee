#include "Note.h"

Note::Note(float x , float y )
{
	this->shape_.setPosition(x, y);
	this->shape_.setRadius(10);
	this->shape_.setFillColor(sf::Color::Green);
}

void Note::UpdatePosition()
{
	sf::Vector2f movement(-0.1f, 0);
	this->shape_.move(movement);
}
