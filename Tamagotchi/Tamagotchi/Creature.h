#pragma once
#include <string>
#include "Nourriture.h"
#include "Medicament.h"
#include <iostream>
#include "SFML\Graphics.hpp"

enum Statut
{
	enforme,
	deprime,
	affame,
	extenue
};



using namespace std;

class Creature
{
public:
	Creature();
	~Creature();

	string getNom();
	void setNom();
	int getPV();
	void setPV();
	int getEnergie();
	void setEnergie();
	int getJoie();
	void setJoie();
	int getStatut();
	void setStatut();
	//int getStade();
	//void setStade();


	int faireCaca();
	//void jouer();
	int laver();


private:

	string nom;
	int pvMax=100;
	int pvActuel;
	int energieMax=100;
	int energieActuel;
	int joieMax=100;
	int joieActuel;
	int statut=enforme;
	//int stade=oeuf;
	bool enVie=true;
	int nbNourris=0;
	int nbCacas=0;
	int nbLave=0;
	int nbSoigne=0;


protected:

};

