#include "Creature.h"

enum Statut
{
	deprime,
	affame,
	extenue
};

enum Stade
{
	oeuf,
	enfant,
	ado,
	adulte
};


Creature::Creature()
{
}


Creature::~Creature()
{
}


string Creature::getNom()
{
	return nom;
}

int Creature::getPV()
{
	return PV;
}

int Creature::getEnergie()
{
	return energie;
}

int Creature::getJoie()
{
	return joie;
}

int Creature::getStatut()
{
	return statut;
}
int Creature::getStade()
{
	return stade;
}

int Creature::donnerAManger()
{
	joie++;
	return nbNourris++;
}

int Creature::faireCaca()
{
	nbNourris = 0;
	return nbCacas++;
}

int Creature::laver()
{
	nbCacas = 0;
	joie++;
	return	nbLave++;
}
int Creature::soigner()
{
	statut = 0;
	return nbSoigne++;
}