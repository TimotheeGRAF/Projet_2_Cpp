#pragma once
#include <string>
#include "Nourriture.h"
#include "Medicament.h"
#include <iostream>
#include "SFML\Graphics.hpp"

enum Statut
{
	idle,
	deprime,
	heureux,
	extenue,
	dort,
	malade

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

	bool enVie = true;
	string getNom();
	void setNom(string nomCrea);
	int getPV();
	void setPV(int pdV);
	int getPVMax();
	int getExpMax();
	void setExpMax(int expM);
	int getExpActuel();
	void setExpActuel(int expGain);
	int getNiveau();
	void setNiveau(int lvl);
	int getStade();
	void setStade(Stade stadeCrea);
	int getEnergie();
	void setEnergie(int nrj);
	int getEnergieMax();
	int getJoie();
	void setJoie(int joie);
	int getJoieMax();
	int getStatut();
	void setStatut(Statut);
	int getFaim();
	void setFaim(int faim);
	int getFaimMax();

	int getNbNourris();
	void setNbNourris(int nbN);
	int getNbCacas();
	void setNbCacas(int nbKK);


	int faireCaca();
	void donnerAManger(Nourriture::typeNourriture, Creature animal);
	int soigner(Medicament::typeMedicament, Creature animal);
	int laver();
	//int gagnerNiveau(Creature animal);
	//void evoluer(Creature animal, Stade stadeCrea);


private:

	Stade stadeCrea;
	Statut stats;
	string nom;
	int pvMax=100;
	int pvActuel=100;
	int energieMax=100;
	int energieActuel=100;
	int joieMax=100;
	int joieActuel=100;
	int expMax = 50;
	int expActuel=0;
	int niveau = 1;
	int faimMax = 100;
	int faimActuel=100;
	int statut=idle;
	int nbNourris=0;
	int nbCacas=0;
	int nbLave=0;
	int nbSoigne=0;


protected:


};

