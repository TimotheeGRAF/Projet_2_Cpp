#include "Nourriture.h"
#include "Creature.h"



Nourriture::Nourriture()
{
}


Nourriture::~Nourriture()
{
}

int Nourriture::donnerAManger(typeNourriture nourriture)
{
	switch (nourriture)
	{
	case fruit:
		cout << "FRUIT" << endl;
		break;
	case viande:
		cout << "VIANDE" << endl;
		break;
	case biscuit:
		cout << "BISCUIT" << endl;
		break;
	default:
		break;
	}

	return compteurNourriture++;
}