#pragma once
#include <string>
#include "Nourriture.h"

using namespace std;

class Creature
{
public:
	Creature();
	~Creature();

	string getNom();
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
	int PV;
	int energie;
	int joie;
	int statut;
	int stade;
	bool enVie;
	int nbNourris;
	int nbCacas;
	int nbLave;
	int nbSoigne;

protected:

};

