#include "Medicament.h"


Medicament::Medicament()
{
}


Medicament::~Medicament()
{
}

int Medicament::soigner(typeMedicament medoc)
{
	switch (medoc)
	{
	case antidepresseur:
		cout << "COCAIN" << endl;
		break;
	case hyperproteine:
		cout << "PROTEIN POWDER" << endl;
		break;
	case stimulant:
		cout << "REDBULL" << endl;
		break;
	default:
		break;
	}

	return nouveauStatut;
}