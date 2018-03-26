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

enum Stade
{
	oeuf,
	enfant,
	adulte
};


using namespace std;

class Creature
{
public:
	Creature();
	~Creature();

	string getNom();
	void setNom(string nomCrea);
	int getPV();
	void setPV(int pdV);
	int getExpMax();
	void setExpMax(int expM);
	int getExpActuel();
	void setExpActuel(int expGain);
	void setStade(Stade stadeEvolution);
	int getEnergie();
	void setEnergie(int nrj);
	int getJoie();
	void setJoie(int joie);
	int getStatut();
	void setStatut(Statut);
	int getFaim();
	void setFaim(int faim);

	int getNbNourris();
	void setNbNourris(int nbN);
	int getNbCacas();
	void setNbCacas(int nbKK);


	int faireCaca();
	int soigner(Medicament::typeMedicament, Creature animal);
	int laver();
	void evoluer(Creature animal, Stade stadeEvolution);


private:

	Stade stadeEvolution;
	Statut stats;
	string nom;
	int pvMax=100;
	int pvActuel;
	int energieMax=100;
	int energieActuel;
	int joieMax=100;
	int joieActuel;
	int expMax = 50;
	int expActuel;
	int niveau = 1;
	int faimMax = 100;
	int faimActuel;
	int statut=enforme;
	bool enVie=true;
	int nbNourris=0;
	int nbCacas=0;
	int nbLave=0;
	int nbSoigne=0;


protected:

};

