#ifndef __MUSIQUE__
#define __MUSIQUE__

#include "Note.h"

#include <list>
#include <string>

using namespace std;
class Musique // Zemmiri/Faure
{
private:
	list<Note> notes_;  // Liste des notes qui compose la musique � jouer
	string nom_; // nom de la musique pour affichage 
	sf::RenderWindow *renderWindow_;// Fenetre o� la musique va �tre affich�e
	sf::CircleShape reticule_; // Reticule qui permet de jouer les notes

	sf::Text scoreText_; // Variable de texte pour affichage du score
	sf::Text retourTiming_; // Variable de texte pour affichage IU

	int score_; // variable de score 
	int difficulty_;// Difficult�

public:
	/**
	Constructeur de Musique
	@param renderWindow Fenetre o� la musique va �tre affich�e
	@param font Police d'�criture utilis�e
	**/
	Musique(sf::RenderWindow &renderWindow,sf::Font &font);
	/**
	 Genere une musique par d�faut qui contient 10 notes bleue.
	**/
	void genererMusique();
	/**
	Met � jour la position des notes ainsi que les indicateurs visuels.
	**/
	void updateMusique();
	/**
	Permet de gerer les evenements du clavier en lien avec la musique comme le fait de jouer une note.
	@param event Evenement sfml qui doit �tre trait�
	**/
	void evenementTouche(sf::Event& event);
	/**
	Genere une musique � partir d'un chemin.
	@param filePath Chaine de caractere qui represente le chemin (relatif ou absolu) du fichier de note qui doit �tre lu.
	**/
	void genererMusique(string filePath);
	/**
	Defini une difficult� � la musique.
	@param difficulty Entier qui defini la difficult�. 1 pour Facile,2 pour Moyen et 3 pour Difficile
	**/
	void setDifficulty(int difficulty);
	/**
	Retourne la note la plus proche du reticule.
	@return Pointeur vers la note la plus proche.
	**/
	Note* getClosestNotePtr();
};

#endif