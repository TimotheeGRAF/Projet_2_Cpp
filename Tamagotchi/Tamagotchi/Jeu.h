#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "Creature.h"
#include "Collision.h"
#include <iostream>
#include <vector>
#include "Sound.h"
#include "Graphics.h"
#include "BDD.h"

class Jeu
{
public:
	Jeu();
	~Jeu();

	enum gameState {
		game,
		menu
	};

	bool onMenu = false;
	bool onOptions = false;

	

	void chooseState(Jeu tamago, Jeu::gameState state);
	void titlescreen();
	void jouer();
	void save(Creature Fox);
	void load(Creature Fox);



private:



protected:


};

