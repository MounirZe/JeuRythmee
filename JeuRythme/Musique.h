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

public:
	Musique(sf::RenderWindow &renderWindow);
	 void genererMusique();
	 void updateMusique();
};

#endif