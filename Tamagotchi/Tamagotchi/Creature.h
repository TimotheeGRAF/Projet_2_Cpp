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
	void setNom(string nomCrea);
	int getPV();
	void setPV(int pdV);
	int getEnergie();
	void setEnergie(int nrj);
	int getJoie();
	void setJoie(int joie);
	int getStatut();
	void setStatut(Statut);
	int getNbNourris();
	void setNbNourris(int nbN);
	int getNbCacas();
	void setNbCacas(int nbKK);


	int faireCaca();
	int soigner(Medicament::typeMedicament, Creature animal);
	int laver();


private:

	Statut stats;
	string nom;
	int pvMax=100;
	int pvActuel;
	int energieMax=100;
	int energieActuel;
	int joieMax=100;
	int joieActuel;
	int statut=enforme;
	bool enVie=true;
	int nbNourris=0;
	int nbCacas=0;
	int nbLave=0;
	int nbSoigne=0;


protected:

};

