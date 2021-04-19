#include "Musique.h"

Musique::Musique(sf::RenderWindow &renderWindow)
{
	this->renderWindow_ = &renderWindow;
}

void Musique::genererMusique()
{
	for (int i = 0; i < 20; i++) {
		Note note(i*100);

		this->notes_.push_back(note);
	}
}

void Musique::updateMusique()
{
	for (Note &note : this->notes_) {
		note.UpdatePosition();
		if(note.getShape().getPosition().x > 0)this->renderWindow_->draw(note.getShape());
	}
}


