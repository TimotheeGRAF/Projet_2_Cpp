#pragma once
#include <string>

using namespace std;

class Nourriture
{
public:
	Nourriture();
	~Nourriture();


private:

	int typeNourriture;

protected:
	int PVrestaure;
	int joieRestaure;
	int energieRestaure;

};

