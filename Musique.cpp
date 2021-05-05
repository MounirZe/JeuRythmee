#include "Musique.h"
#include <iostream>
using namespace std;

Musique::Musique(sf::RenderWindow &renderWindow)
{
	this->renderWindow_ = &renderWindow;
}

void Musique::genererMusique()
{
	this->reticule_.setPosition(50,250);
	this->reticule_.setRadius(10);
	this->reticule_.setFillColor(sf::Color::White);
	this->reticule_.setOutlineThickness(4);
	this->reticule_.setOutlineColor(sf::Color::Red);

	this->score_ = 0;
	for (int i = 0; i < 20; i++) {
		Note note(TypeNoteEnum::Bleue, i * 100);
		this->notes_.push_back(note);
	}
}

void Musique::updateMusique()
{
	this->renderWindow_->draw(this->reticule_);

	for (Note &note : this->notes_) {
		note.UpdatePosition();
		if(note.getShape().getPosition().x > 0)this->renderWindow_->draw(note.getShape());
		//TODO: Suppression objet
	}

}

void Musique::evenementTouche(sf::Event& event)
{
	Note* currNote = this->getClosestNotePtr();
	if (currNote == nullptr) return;
	list<sf::Keyboard::Key> keys = currNote->getTypeNote().getKeys();

	if (std::find(keys.begin(), keys.end(), event.key.code) != keys.end()) {
		int distance = abs(currNote->getShape().getPosition().x - this->reticule_.getPosition().x);
		if (distance < 100 && !currNote->isPlayed()) {
			if (currNote->getShape().getPosition().x < 35)
			{
				com_ = "Trop tard!";
			}
			else if (currNote->getShape().getPosition().x > 65)
			{
				com_ = "Trop tot!";
			}
			else if ((currNote->getShape().getPosition().x < 45 && currNote->getShape().getPosition().x > 35) || (currNote->getShape().getPosition().x > 55 && currNote->getShape().getPosition().x < 65))
			{
				score_ += 50;
				com_ = "Super!";
			}
			else if (currNote->getShape().getPosition().x <= 55 && currNote->getShape().getPosition().x >= 45)
			{
				score_ += 100;
				com_ = "Parfait!";
			}
			currNote->setPlayed(true);
			cout << currNote->getShape().getPosition().x << endl;
		} 

	}
}

Note* Musique::getClosestNotePtr()
{
	if(this->notes_.empty()) return nullptr;

    Note* noteptr = &this->notes_.front();


	int minX = abs((*noteptr).getShape().getPosition().x - this->reticule_.getPosition().x);

	for (Note& note : this->notes_) {
		int curX = abs(note.getShape().getPosition().x - this->reticule_.getPosition().x);
		if (curX < minX) {
			minX = curX; 
			noteptr = &note;
		}
	}
	return noteptr;
}

