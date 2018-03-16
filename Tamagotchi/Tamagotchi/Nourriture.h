#pragma once
#include "Creature.h"

using namespace std;

enum typeNourriture
{
	fruit,
	viande,
	biscuit
};


class Nourriture
{
public:
	Nourriture();
	~Nourriture();


	int donnerAManger(typeNourriture);
	sf::Sprite spriteNourriture;

private:


protected:
	int compteurNourriture=0;
	int PVrestaure;
	int joieRestaure;
	int faimRestaure;



};

