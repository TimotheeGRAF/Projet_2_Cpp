#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "Creature.h"
#include <iostream>
#include <vector>
#include <SFML\Audio\Sound.hpp>
#include <SFML\Audio\SoundBuffer.hpp>
#include <SFML\Audio\Music.hpp>
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
	string quotesql(const string& s);

	void chooseState(Jeu tamago, Jeu::gameState state, Creature creature);
	void titlescreen(Creature creature);
	void jouer(Creature creature);
	bool save(Creature creature);
	Creature load();

private:

	sqlite3 * db;
	string dbfile;

protected:

};