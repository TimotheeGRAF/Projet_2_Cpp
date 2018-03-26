#include "Creature.h"
#include <string>
#include <iostream>

Creature::Creature()
{
}
Creature::~Creature()
{
}

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




int Creature::faireCaca()
{
	this->nbNourris = 0;
	return this->nbCacas++;
}



int Creature::laver()
{
	this->nbCacas = 0;
	this->joieActuel++;
	return this->nbLave++;
}

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

void Creature::setFaim(int faimGain)
{
	this->faimActuel = faimActuel + faimGain;
}