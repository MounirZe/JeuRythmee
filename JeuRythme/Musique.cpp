#include "Musique.h"
#include <iostream>
#include <fstream>
using namespace std;

Musique::Musique(sf::RenderWindow& renderWindow,sf::Font &font) : renderWindow_(&renderWindow), difficulty_(1), score_(0)
{

	this->retourTiming_.setCharacterSize(40); // Définition des différents paramètres de retourTiming_ et scoreText_
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

	// Initialisation du stream et chargement du fichier
	ifstream myfile;
	myfile.open(filePath);

	string line;

	string delimiter = " ";
	if (myfile.is_open()) // Si le chargement a fonctionné 
	{
		while (getline(myfile, line)) // Tant que la lecture n'est pas finie, lecture de la ligne et stock la ligne dans line
		{
			/* Ici on parse chaque ligne : 
			* Une ligne est sous la forme : typeNote Position 
			* typeNote : Un entier qui represente le type de Note, 1 pour Bleue 2 pour Rouge et 3 pour Orange
			*/
			int typeNote = stoi(line.substr(0, line.find(delimiter)));  // Recupere le type de note et le converti en int 
			line.erase(0, line.find(delimiter) + delimiter.length()); // Supprime la partie qui indique le type de note, la partie qui reste est donc la position de la note
			int distance = stoi(line); // Conversion en entier de la position de la note
			TypeNoteEnum typeNoteEnum; 
			switch (typeNote) { // En fonction du typeNote on defini le type de notre note
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
			Note note(typeNoteEnum, distance); // Création d'une note du type souhaité et à la distance souhaitée
			this->notes_.push_back(note); // Stock la note dans la liste
		}
		myfile.close();
	}
	// Gestion du reticule
	this->reticule_.setPosition(50, 250); 
	this->reticule_.setRadius(10);
	this->reticule_.setFillColor(sf::Color::White);
	this->reticule_.setOutlineThickness(4);
	this->reticule_.setOutlineColor(sf::Color::Red);

}

void Musique::genererMusique()
{

	// Gestion du reticule
	this->reticule_.setPosition(50, 250);
	this->reticule_.setRadius(10);
	this->reticule_.setFillColor(sf::Color::White);
	this->reticule_.setOutlineThickness(4);
	this->reticule_.setOutlineColor(sf::Color::Red);

	// Generation de 20 note Bleue equidistants de 100 
	for (int i = 0; i < 20; i++) {
		Note note(TypeNoteEnum::Bleue, i * 100);
		this->notes_.push_back(note);
	}
}

void Musique::updateMusique()
{
	// Mise à jour de la musique, dessine le reticule, le score et l'indicateur de timing
	this->renderWindow_->draw(this->reticule_);
	this->renderWindow_->draw(this->retourTiming_);
	this->renderWindow_->draw(this->scoreText_);


	for (Note &note : this->notes_) { // Pour toutes les notes, 
		note.UpdatePosition(this->difficulty_*0.1f);// mise à jour de la position en fonction de la difficulté 
		if (note.getPosition().x > 0)this->renderWindow_->draw(note); // Si la note est théoriquement visible (x>0) dessine la note
	}

}

void Musique::evenementTouche(sf::Event& event)
{
	Note* currNote = this->getClosestNotePtr(); // Recupere la note la plus proche
	if (currNote == nullptr) return;
	list<sf::Keyboard::Key> keys = currNote->getTypeNote().getKeys(); // Recupere les touches associés à la note

	if (std::find(keys.begin(), keys.end(), event.key.code) != keys.end()) { // Si la touche appuyée appartient aux touches qui doivent etre appuyées
		int distance = abs(currNote->getPosition().x - this->reticule_.getPosition().x); // Distance par rapport au reticule
		if (distance < 100 && !currNote->isPlayed()) { // Si la note n'est pas encore jouée et qu'elle se trouve proche du reticule
			string retourTimingStr;
			// Mise à jour du score et de l'indicateur de timing en fonction de la distance
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
			// La note a été jouée
			currNote->setPlayed(true);
			// Mise à jour des indicateurs visuels (score et timing)
			retourTiming_.setString(retourTimingStr);
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

	for (Note& note : this->notes_) { // On cherche la distance minimale par rapport au reticule
		int curX = abs(note.getPosition().x - this->reticule_.getPosition().x);
		if (curX < minX) {
			minX = curX;
			noteptr = &note;
		}
	}
	return noteptr;
}