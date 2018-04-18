#include "Jeu.h"


int main()
{
	Jeu Tamagotchi;
	Creature Bestiole;

	Tamagotchi.openDatabase();
	Tamagotchi.executeQuery("CREATE TABLE IF NOT EXISTS Creature (pv INT, faim INT, nrj INT, joie INT, nbCaca INT, nbNourris INT, compteurClic INT)");

	Tamagotchi.chooseState(Tamagotchi, Tamagotchi.menu, Bestiole);

	Tamagotchi.closeDatabase();
	return 0;
}