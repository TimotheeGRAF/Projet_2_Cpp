#pragma once
#include <iostream>

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

private:


protected:
	int compteurNourriture=0;

	typeNourriture nourriture;

};

