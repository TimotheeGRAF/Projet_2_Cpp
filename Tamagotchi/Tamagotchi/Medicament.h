#pragma once
#include "Nourriture.h"
#include "Creature.h"

enum typeMedicament
{
	antidepresseur,
	hyperproteine,
	stimulant
};

class Medicament : public Nourriture
{
public:
	Medicament();
	~Medicament();

	int soigner(typeMedicament);

private:

protected:
	int nouveauStatut;

};

