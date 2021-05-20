#ifndef __MUSIQUE__
#define __MUSIQUE__

#include "Note.h"

#include <list>
#include <string>

using namespace std;
class Musique
{
private:
	list<Note> notes_;  // Liste des notes qui compose la musique à jouer
	string nom_; // nom de la musique pour affichage 
	sf::RenderWindow *renderWindow_;
	sf::CircleShape reticule_;
	int score_; // variable de score 
	int difficulty_;
	string retourTiming_; // variable de texte pour l'affichage du timing pour utilisateur 

public:
	Musique(sf::RenderWindow &renderWindow);
	 void genererMusique();
	 void updateMusique();
	 void evenementTouche(sf::Event& event);
	 void genererMusique(string filePath);

	 void setDifficulty(int difficulty);
	 Note* getClosestNotePtr();
	 inline int getScore() const { return this->score_; }
	 inline string getRetourTiming() const { return this->retourTiming_; }
};

#endif