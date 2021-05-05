#ifndef __MUSIQUE__
#define __MUSIQUE__

#include "Note.h"

#include <list>
#include <string>

using namespace std;
class Musique
{
private:
	list<Note> notes_;
	string nom_;
	sf::RenderWindow *renderWindow_;
	sf::CircleShape reticule_;
	int score_;
	string com_;

public:
	Musique(sf::RenderWindow &renderWindow);
	 void genererMusique();
	 void updateMusique();
	 void evenementTouche(sf::Event& event);

	 Note* getClosestNotePtr();
	 inline int getScore() const { return this->score_; }
	 inline string getCom() const { return this->com_; }
};

#endif