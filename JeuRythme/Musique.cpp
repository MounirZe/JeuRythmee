#include "Musique.h"
#include <iostream>
#include <fstream>
using namespace std;

Musique::Musique(sf::RenderWindow &renderWindow)
{
	this->renderWindow_ = &renderWindow;
}
void Musique::genererMusique(string filePath)
{
	this->reticule_.setPosition(50, 250);
	ifstream myfile;
	myfile.open(filePath);
	string line;

	string delimiter = " ";
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
				break;
			case 2:
				typeNoteEnum = TypeNoteEnum::Rouge;
				break;
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
		note.UpdatePosition(this->difficulty_*0.1f);
		if(note.getPosition().x > 0)this->renderWindow_->draw(note);
		//TODO: Suppression objet
	}

}

void Musique::evenementTouche(sf::Event& event)
{
	Note* currNote = this->getClosestNotePtr();
	if (currNote == nullptr) return;
	list<sf::Keyboard::Key> keys = currNote->getTypeNote().getKeys();

	if (std::find(keys.begin(), keys.end(), event.key.code) != keys.end()) {
		int distance = abs(currNote->getPosition().x - this->reticule_.getPosition().x);
		if (distance < 100 && !currNote->isPlayed()) {
			if (distance > 15) {
				if (currNote->getPosition().x < this->reticule_.getPosition().x)
				{
					retourTiming_ = "Trop tard!";
				}
				else
				{
					retourTiming_ = "Trop tot!";
					currNote->setFillColor(sf::Color::Transparent);
				}
			}

			if (distance > 5 && distance < 15)
			{
				score_ += 50*this->difficulty_;
				retourTiming_ = "Super!";
				currNote->setFillColor(sf::Color::Green);
			}
			else if (distance <= 5)
			{
				score_ += 100* this->difficulty_;
				retourTiming_ = "Parfait!";
				currNote->setFillColor(sf::Color::Green);
			}
			currNote->setPlayed(true);
		} 

	}
}

void Musique::setDifficulty(int difficulty)
{
	this->difficulty_ = difficulty;
}

Note* Musique::getClosestNotePtr()
{
	if(this->notes_.empty()) return nullptr;

    Note* noteptr = &this->notes_.front();


	int minX = abs((*noteptr).getPosition().x - this->reticule_.getPosition().x);

	for (Note& note : this->notes_) {
		int curX = abs(note.getPosition().x - this->reticule_.getPosition().x);
		if (curX < minX) {
			minX = curX; 
			noteptr = &note;
		}
	}
	return noteptr;
}


