#pragma once
#include "Creature.h"

using namespace std;




class Nourriture
{
public:
	Nourriture();
	~Nourriture();

	enum typeNourriture
	{
		fruit,
		viande,
		biscuit
	};

	int donnerAManger(typeNourriture);


private:


protected:
	int compteurNourriture=0;
	int PVrestaure;
	int joieRestaure;
	int faimRestaure;



};

