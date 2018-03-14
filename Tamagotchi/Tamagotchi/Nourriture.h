#pragma once
#include "Creature.h"

using namespace std;

enum typeNourriture
{
	fruit,
	viande,
	bonbon
};


class Nourriture
{
public:
	Nourriture();
	~Nourriture();
	int donnerAManger(typeNourriture);

private:


protected:
	int compteurNourriture=0;
	int PVrestaure;
	int joieRestaure;
	int faimRestaure;


};

