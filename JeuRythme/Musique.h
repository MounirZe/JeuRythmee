#ifndef __MUSIQUE__
#define __MUSIQUE__

#include "Note.h"

#include <list>
#include <string>

using namespace std;
class Musique // Zemmiri/Faure
{
private:
	list<Note> notes_;  // Liste des notes qui compose la musique à jouer
	string nom_; // nom de la musique pour affichage 
	sf::RenderWindow *renderWindow_;
	sf::CircleShape reticule_;

	sf::Text scoreText_; 
	sf::Text retourTiming_; // Variable de texte pour affichage IU

	int score_; // variable de score 
	int difficulty_;

public:
	Musique(sf::RenderWindow &renderWindow,sf::Font &font);
	void genererMusique();
	void updateMusique();
	void evenementTouche(sf::Event& event);
	void genererMusique(string filePath);

	void setDifficulty(int difficulty);
	Note* getClosestNotePtr();
};

#endif