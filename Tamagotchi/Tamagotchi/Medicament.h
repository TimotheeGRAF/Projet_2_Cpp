#pragma once
#include "Nourriture.h"
#include "Creature.h"



class Medicament : public Nourriture
{
public:
	Medicament();
	~Medicament();

	enum typeMedicament
	{
		antidepresseur,
		hyperproteine,
		stimulant
	};

	int soigner(typeMedicament);

private:

protected:
	int nouveauStatut;

};

