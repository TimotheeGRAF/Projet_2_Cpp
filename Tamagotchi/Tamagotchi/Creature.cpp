#include "Creature.h"
#include <string>
#include <iostream>

Creature::Creature()
{
}
Creature::~Creature()
{
}


//GETTEURS ET SETTEURS
string Creature::getNom()
{
	return this->nom;
}
void Creature::setNom(string nomCrea)
{
	this->nom = nomCrea;
}

int Creature::getPV()
{
	return pvActuel;
}
void Creature::setPV(int pdV)
{
	this->pvActuel = pdV;
}

int Creature::getEnergie()
{
	return energieActuel;
}
void Creature::setEnergie(int nrj)
{
	this->energieActuel = nrj;
}

int Creature::getJoie()
{
	return joieActuel;
}
void Creature::setJoie(int joie)
{
	this->energieActuel = joie;
}

int Creature::getStatut()
{
	return statut;
}
void Creature::setStatut(Statut stats)
{
	this->statut = stats;
}

int Creature::getNiveau()
{
	return niveau;
}
void Creature::setNiveau(int lvl)
{
	this->niveau = niveau + lvl;
}

void Creature::setStade(Stade stadeE)
{
	this->stadeEvolution = stadeE;
}

int Creature::getNbNourris()
{
	return nbNourris;
}
void Creature::setNbNourris(int nbN)
{
	this->nbNourris = nbN;
}

int Creature::getNbCacas()
{
	return nbCacas;
}
void Creature::setNbCacas(int nbKK)
{
	this->nbCacas = nbKK;
}

int Creature::getExpMax()
{
	return expMax;
}
void Creature::setExpMax(int expM)
{
	this->expMax = expM;
}

int Creature::getExpActuel()
{
	return expActuel;
}
void Creature::setExpActuel(int expGain)
{
	this->expActuel = expActuel + expGain;
}

int Creature::getFaim()
{
	return faimActuel;
}
void Creature::setFaim(int faim)
{
	this->faimActuel =faim;
}



//METHODES DES INTERACTIONS
//Faire ses besoins
int Creature::faireCaca()
{
	this->nbNourris = 0;
	return this->nbCacas++;
}


//Laver Creature et enlever les étrons
int Creature::laver()
{
	this->nbCacas = 0;
	this->joieActuel++;
	return this->nbLave++;
}

//Soigner Creature et changer statut
int Creature::soigner(Medicament::typeMedicament medoc, Creature animal)
{
	switch (medoc)
	{
	case Medicament::typeMedicament::antidepresseur:
		cout << "COCAIN" << endl;
		animal.setStatut(enforme);
		break;
	case Medicament::typeMedicament::hyperproteine:
		cout << "PROTEIN POWDER" << endl;

		animal.setStatut(enforme);

		break;
	case Medicament::typeMedicament::stimulant:
		cout << "REDBULL" << endl;

		animal.setStatut(enforme);

		break;
	default:
		break;
	}

	return animal.getStatut();
}

// Level Up !
int Creature::gagnerNiveau(Creature animal)
{
	animal.setNiveau(+1);
	animal.pvMax = animal.pvMax + 15;
	animal.energieMax = animal.energieMax + 10;
	animal.joieMax = animal.joieMax + 10;
	animal.faimMax = animal.faimMax + 10;
	animal.expMax = animal.expMax + 50;

	animal.setPV(animal.pvMax);
	animal.setEnergie(animal.energieMax);
	animal.setJoie(animal.joieMax);
	animal.setFaim(animal.faimMax);

	return animal.getNiveau();
}

//Evolution de la créature selon son stade
void Creature::evoluer(Creature animal, Stade stadeEvolution)
{
	switch (stadeEvolution)
	{
	case oeuf:
		animal.setStade(enfant);
		break;

	case enfant:
		animal.setStade(adulte);
		break;

	default:
		break;
	}
}