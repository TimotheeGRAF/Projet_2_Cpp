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
void Creature::setStatut()
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
