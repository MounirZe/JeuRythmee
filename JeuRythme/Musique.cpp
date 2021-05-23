#include "Musique.h"
#include <iostream>
#include <fstream>
using namespace std;

Musique::Musique(sf::RenderWindow& renderWindow,sf::Font &font) : renderWindow_(&renderWindow), difficulty_(1), score_(0)
{

	this->retourTiming_.setCharacterSize(40); // Définition des différents paramètres de retourTiming
	this->retourTiming_.setFillColor(sf::Color::White);
	this->retourTiming_.setFont(font);
	this->retourTiming_.setOutlineColor(sf::Color::Red);
	this->retourTiming_.setOutlineThickness(4);
	this->retourTiming_.setPosition(300, 100);
	this->retourTiming_.setString("");

	this->scoreText_.setString(std::to_string(score_));
	this->scoreText_.setCharacterSize(20);
	this->scoreText_.setFillColor(sf::Color::Red);
	this->scoreText_.setFont(font);


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
			case 3:

				typeNoteEnum = TypeNoteEnum::Orange;
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
	this->reticule_.setPosition(50, 250);
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
	this->renderWindow_->draw(this->retourTiming_);
	this->renderWindow_->draw(this->scoreText_);


	for (Note &note : this->notes_) {
		note.UpdatePosition(this->difficulty_*0.1f);
		if (note.getPosition().x > 0)this->renderWindow_->draw(note);
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
			string retourTimingStr;
			if (distance > 15) {
				if (currNote->getPosition().x < this->reticule_.getPosition().x)
				{
					retourTimingStr = "Trop tard!";
				}
				else
				{
					retourTiming_.setString( "Trop tot!");
					currNote->setFillColor(sf::Color::Transparent);
				}
			}

			if (distance > 5 && distance < 15)
			{
				score_ += 50 * this->difficulty_;
				retourTimingStr = "Super!";
				currNote->setFillColor(sf::Color::Green);
			}
			else if (distance <= 5)
			{
				score_ += 100 * this->difficulty_;
				retourTimingStr = "Parfait!";
				currNote->setFillColor(sf::Color::Green);
			}
			retourTiming_.setString(retourTimingStr);
			currNote->setPlayed(true);
			scoreText_.setString(std::to_string(score_));
		}

	}
}

void Musique::setDifficulty(int difficulty)
{
	this->difficulty_ = difficulty;
}

Note* Musique::getClosestNotePtr()
{
	if (this->notes_.empty()) return nullptr;

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