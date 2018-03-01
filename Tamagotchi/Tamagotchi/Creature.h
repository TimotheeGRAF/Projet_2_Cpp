#pragma once
#include <string>
#include "Nourriture.h"
#include <iostream>
#include "SFML\Graphics.hpp"

using namespace std;

class Creature
{
public:
	Creature();
	~Creature();

	string getNom();
	void setNom();
	int getPV();
	int getEnergie();
	int getJoie();
	int getStatut();
	int getStade();
	int faireCaca();
	void jouer();
	int donnerAManger();
	int soigner();
	int laver();

private:

	string nom;
	int PV=100;
	int energie=100;
	int joie=100;
	int statut=0;
	int stade=0;
	bool enVie=true;
	int nbNourris=0;
	int nbCacas=0;
	int nbLave=0;
	int nbSoigne=0;

protected:

};

