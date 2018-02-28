#pragma once
#include <string>

using namespace std;

class Creature
{
public:
	Creature();
	~Creature();

	string getNom();
	int getPV();
	int getEnergie();
	int getJoie();
	int getStatut();
	int getStade();
	void faireCaca();
	void tomberMalade();
	

private:

	string nom;
	int PV;
	int energie;
	int joie;
	int statut;
	int stade;
	bool enVie;

protected:

};

