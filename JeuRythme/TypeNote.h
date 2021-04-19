#ifndef __TYPENOTE__
#define __TYPENOTE__

#include <list>
using namespace std;
#include <SFML/Graphics.hpp>


class TypeNote
{
private:
	sf::Color couleur_;
	list<char> toucheClavier_;
};

#endif