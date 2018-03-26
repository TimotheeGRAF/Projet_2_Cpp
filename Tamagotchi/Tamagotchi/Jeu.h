#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "Creature.h"
#include "Collision.h"
#include <iostream>

class Jeu
{
public:
	Jeu();
	~Jeu();

	enum gameState {
		game,
		menu,
		save,
		load,
		igmenu
	};

	void jouer();

private:



protected:

};

