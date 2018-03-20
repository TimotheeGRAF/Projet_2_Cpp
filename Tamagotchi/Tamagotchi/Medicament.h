#pragma once
#include "Creature.h"

class Medicament
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

	typeMedicament medoc;
};

