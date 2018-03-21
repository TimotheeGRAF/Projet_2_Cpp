#include "Nourriture.h"




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
		PVrestaure = 10;
		joieRestaure = 10;
		faimRestaure = 5;
		break;
	case viande:
		cout << "VIANDE" << endl;
		PVrestaure = 5;
		joieRestaure = 5;
		faimRestaure = 15;
		break;
	case biscuit:
		cout << "BISCUIT" << endl;
		PVrestaure = -5;
		joieRestaure = 15;
		faimRestaure = 5;
		break;

	default:
		break;
	}

	return compteurNourriture++;
}