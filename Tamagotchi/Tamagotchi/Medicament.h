#pragma once
#include "Nourriture.h"

class Medicament
{
public:
	Medicament();
	~Medicament();

	int getMedicament();
	void guerirStatut();

private:
	int typeMedicament;
protected:

};

