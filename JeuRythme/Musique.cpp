#include "Musique.h"
#include <iostream>
#include <fstream>
using namespace std;

Musique::Musique(sf::RenderWindow &renderWindow)
{
	this->renderWindow_ = &renderWindow;
}
void Musique::genererMusique(string file_)
{
	ifstream myfile;
	myfile.open(file_);
	string line;

	string delimiter = ">=";
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			int typeNote = stoi(line.substr(0, line.find(delimiter)));
			line.erase(0, line.find(delimiter) + delimiter.length());
			int distance = stoi(line);
			TypeNoteEnum typeNoteEnum;
			switch (typeNote) {
			case 1:
				typeNoteEnum = TypeNoteEnum::Bleue;
			case 2:
				typeNoteEnum = TypeNoteEnum::Rouge;
			default:
				typeNoteEnum = TypeNoteEnum::Rouge;
			}
			Note note(typeNoteEnum, distance);
			this->notes_.push_back(note);
		}
		myfile.close();
	}
	this->reticule_.setPosition(50, 250);
	this->reticule_.setRadius(10);
	this->reticule_.setFillColor(sf::Color::White);
	this->reticule_.setOutlineThickness(4);
	this->reticule_.setOutlineColor(sf::Color::Red);

	this->score_ = 0;
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
		int distance = abs(currNote->getShape().getPosition().x - this->reticule_.getPosition().x); // TODO : Verifier le retour de getPos().x
		if (distance < 100 && !currNote->isPlayed()) {
			if(distance > 15){
				if (currNote->getShape().getPosition().x < this->reticule_.getPosition().x)
				{
					com_ = "Trop tard!";
				}
				else
				{
					com_ = "Trop tot!";
				}
			}

			if (distance > 5 && distance < 15)
			{
				score_ += 50;
				com_ = "Super!";
			}
			else if (distance <= 5)
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


