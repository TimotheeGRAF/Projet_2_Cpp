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
void Creature::setNom()
{
 this->nom="Poupette";
}

int Creature::getPV()
{
	return pvActuel;
}
void Creature::setPV()
{
	this->pvActuel = 100;
}

int Creature::getEnergie()
{
	return energieActuel;
}
void Creature::setEnergie()
{
	this->energieActuel = 100;
}

int Creature::getJoie()
{
	return joieActuel;
}
void Creature::setJoie()
{
	this->energieActuel = 100;
}

int Creature::getStatut()
{
	return statut;
}
void Creature::setStatut(Statut stats)
{
	this->statut = enforme;
}



int Creature::faireCaca()
{
	nbNourris = 0;
	return nbCacas++;
}

int Creature::laver()
{
	nbCacas = 0;
	joieActuel++;
	return	nbLave++;
}

int Creature::soigner(Medicament::typeMedicament medoc, Creature animal)
{
	switch (medoc)
	{
	case Medicament::typeMedicament::antidepresseur:
		cout << "COCAIN" << endl;
		animal.setStatut(deprime);
		break;
	case Medicament::typeMedicament::hyperproteine:
		cout << "PROTEIN POWDER" << endl;

		animal.setStatut(affame);

		break;
	case Medicament::typeMedicament::stimulant:
		cout << "REDBULL" << endl;

		animal.setStatut(extenue);

		break;
	default:
		break;
	}

	return animal.getStatut();
}