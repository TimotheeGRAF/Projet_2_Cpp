#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "Creature.h"
#include <iostream>
#include <vector>
#include <SFML\Audio\Sound.hpp>
#include <SFML\Audio\SoundBuffer.hpp>
#include "sqlite3.h"


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

	void openDatabase();
	void closeDatabase();
	bool executeQuery(string query);

	

	void chooseState(Jeu tamago, Jeu::gameState state);
	void titlescreen();
	void jouer();
	bool save(int pv, int faim, int nrj, int joie, int nbCaca, int nbNourris);
	vector<Creature*>* load();



private:

	sqlite3 * db;
	string dbfile;

protected:


};

