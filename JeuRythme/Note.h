#ifndef __NOTE__
#define __NOTE__
#include "TypeNote.h"
#include <SFML/Graphics.hpp>

class Note : public sf::CircleShape // Zemmiri/Faure
{

private:
	TypeNote typeNote_; // note rouge ou bleu 
	bool played_; // variable binaire qui indique si la note a deja été jouée ou non 
public:
	Note(TypeNoteEnum typeNote, float x = 0, float y = 250);
	void UpdatePosition(float speed);

	inline TypeNote getTypeNote() const { return this->typeNote_; }


	inline bool isPlayed() const { return played_; }
	inline void setPlayed(bool state) { played_ = state; }

};
#endif 