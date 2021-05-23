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
	sf::RenderWindow *renderWindow_;// Fenetre où la musique va être affichée
	sf::CircleShape reticule_; // Reticule qui permet de jouer les notes

	sf::Text scoreText_; // Variable de texte pour affichage du score
	sf::Text retourTiming_; // Variable de texte pour affichage IU

	int score_; // variable de score 
	int difficulty_;// Difficulté

public:
	/**
	Constructeur de Musique
	@param renderWindow Fenetre où la musique va être affichée
	@param font Police d'écriture utilisée
	**/
	Musique(sf::RenderWindow &renderWindow,sf::Font &font);
	/**
	 Genere une musique par défaut qui contient 10 notes bleue.
	**/
	void genererMusique();
	/**
	Met à jour la position des notes ainsi que les indicateurs visuels.
	**/
	void updateMusique();
	/**
	Permet de gerer les evenements du clavier en lien avec la musique comme le fait de jouer une note.
	@param event Evenement sfml qui doit être traité
	**/
	void evenementTouche(sf::Event& event);
	/**
	Genere une musique à partir d'un chemin.
	@param filePath Chaine de caractere qui represente le chemin (relatif ou absolu) du fichier de note qui doit être lu.
	**/
	void genererMusique(string filePath);
	/**
	Defini une difficulté à la musique.
	@param difficulty Entier qui defini la difficulté. 1 pour Facile,2 pour Moyen et 3 pour Difficile
	**/
	void setDifficulty(int difficulty);
	/**
	Retourne la note la plus proche du reticule.
	@return Pointeur vers la note la plus proche.
	**/
	Note* getClosestNotePtr();
};

#endif