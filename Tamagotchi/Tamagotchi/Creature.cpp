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
	std::cout << "Quel sera le nom de ta petite bestiole ?" << std::endl;
	std::cin >> this->nom;
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

int Creature::getStade()
{
	return stade;
}
void Creature::setStade()
{
	this->stade = oeuf;
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
