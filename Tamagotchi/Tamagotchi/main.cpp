#include "Jeu.h"


int main()
{
	Jeu Tamagotchi;

	Tamagotchi.openDatabase();
	Tamagotchi.executeQuery("CREATE TABLE IF NOT EXISTS Creature (pv INT, faim INT, nrj INT, joie INT, nbCaca INT, nbNourris INT)");

	Tamagotchi.chooseState(Tamagotchi, Tamagotchi.menu);



	Tamagotchi.closeDatabase();
	return 0;
}