#include "Jeu.h"

using namespace std;

Jeu::Jeu()
{
	dbfile = "./database.db";
}

Jeu::~Jeu()
{
}

void Jeu::openDatabase()
{
	sqlite3_initialize();
	sqlite3_open(dbfile.c_str(), &db);
}

void Jeu::closeDatabase()
{
	sqlite3_close_v2(db);
	sqlite3_shutdown();
}

bool Jeu::executeQuery(string query)
{
	char * errmsg = 0;
	if (sqlite3_exec(db, query.c_str(), NULL, 0, &errmsg) != SQLITE_OK)
	{
		return false;
	}
	else
	{
		return true;
	}
}

string Jeu::quotesql(const string& s) {
	return string("'") + s + string("'");
}

bool Jeu::save(Creature animal)
{
	char bpv[10];
	char bfaim[10];
	char bnrj[10];
	char bjoie[10];
	char bnbCaca[10];
	char bnbNourris[10];
	char bcompteurClic[10];

	sprintf_s(bpv, "%d", animal.getPV());
	sprintf_s(bfaim, "%d", animal.getFaim());
	sprintf_s(bnrj, "%d", animal.getEnergie());
	sprintf_s(bjoie, "%d", animal.getJoie());
	sprintf_s(bnbCaca, "%d", animal.getNbCacas());
	sprintf_s(bnbNourris, "%d", animal.getNbNourris());
	sprintf_s(bcompteurClic, "%d", animal.compteurClic);



	string query = "INSERT INTO Creature (pv, faim, nrj, joie, nbCaca, nbNourris, compteurClic) VALUES ("
		+ quotesql(bpv) + ","
		+ quotesql(bfaim) + ","
		+ quotesql(bnrj) + ","
		+ quotesql(bjoie) + ","
		+ quotesql(bnbCaca) + ","
		+ quotesql(bnbNourris) + ","
		+ quotesql(bcompteurClic) + ");";

	return executeQuery(query);
}

Creature Jeu::load()
{
	Creature animal;

	string query = "SELECT rowid, * FROM Creature";
	int i;

	sqlite3_stmt * stmt;
	sqlite3_prepare_v2(db, query.c_str(), strlen(query.c_str()) + 1, &stmt, NULL);

	do {
		i = sqlite3_step(stmt);
		if (i == SQLITE_ROW)
		{
			animal.setPV(sqlite3_column_int(stmt, 1));
			animal.setFaim(sqlite3_column_int(stmt, 2));
			animal.setEnergie(sqlite3_column_int(stmt, 3));
			animal.setJoie(sqlite3_column_int(stmt, 4));
			animal.setNbCacas(sqlite3_column_int(stmt, 5));
			animal.setNbNourris(sqlite3_column_int(stmt, 6));
			animal.compteurClic = sqlite3_column_int(stmt, 7);
		}
	} while (i == SQLITE_ROW);
	return animal;
}

void Jeu::chooseState(Jeu tamago, Jeu::gameState state, Creature Bestiole)
{
	switch (state)
	{
	case game:
		tamago.jouer(Bestiole);
		break;
	case menu:
		tamago.titlescreen(Bestiole);
		break;
	default:
		break;
	}
}

void Jeu::titlescreen(Creature Bestiole)
{
	sf::RenderWindow window(sf::VideoMode(665, 800), "What does the fox say ?");

	//Curseur
	sf::Vector2i posSouris;
	sf::Texture cursor;
	cursor.loadFromFile("Cursor.png");
	sf::IntRect rectCursor(0, 0, 32, 38);
	sf::Sprite spriteCursorTitre(cursor, rectCursor);
	window.setMouseCursorVisible(false);

	//Boutons
	sf::IntRect rectBoutons(0, 0, 180, 25);
	sf::Texture alpha;
	sf::Sprite spriteBoutons(alpha, rectBoutons);
	spriteBoutons.setColor(sf::Color::Red);
	//Création vector de sprites boutons
	vector<sf::Sprite> boutonsMenu;
	for (int i = 0; i <= 3; i++)
	{
		boutonsMenu.push_back(spriteBoutons);
	}
	//Boutons menu ig/main
	boutonsMenu[0].setPosition(240, 285);	//Nouvelle partie
	boutonsMenu[1].setPosition(240, 342);	//Charger
	boutonsMenu[2].setPosition(240, 400);	//Options
	boutonsMenu[3].setPosition(240, 536);	//Quitter


	//Background
	sf::Texture backgroundTitre;
	backgroundTitre.loadFromFile("background.png");
	sf::Sprite spriteBackgroundTitre(backgroundTitre);


	while (window.isOpen())
	{
		//Creation event catcher
		sf::Event event;

		while (window.pollEvent(event))
		{
			spriteCursorTitre.setPosition((sf::Vector2f)sf::Mouse::getPosition(window));

			if (event.type == sf::Event::Closed || (boutonsMenu[3].getGlobalBounds().intersects(spriteCursorTitre.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
			{
				window.close();
			}

			if ((boutonsMenu[0].getGlobalBounds().intersects(spriteCursorTitre.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
			{
				window.close();
				jouer(Bestiole);
			}

			if ((boutonsMenu[1].getGlobalBounds().intersects(spriteCursorTitre.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
			{
				window.close();
				jouer(load());
			}

			if ((boutonsMenu[2].getGlobalBounds().intersects(spriteCursorTitre.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
			{

			}

		}


		window.clear();

		window.draw(boutonsMenu[0]);
		window.draw(boutonsMenu[1]);
		window.draw(boutonsMenu[3]);

		window.draw(spriteBackgroundTitre);
		window.draw(spriteCursorTitre);

		window.display();
	}
}

void Jeu::jouer(Creature Bestiole)
{
	sf::RenderWindow window(sf::VideoMode(665, 800), "TamaGoGo !");

	//Creation créature
	Bestiole.setStade(oeuf);
	//Creation nourriture
	Nourriture Repas;
	//Creation medicament
	Medicament Soin;
	//Variables globales
	bool isDay = true;
	bool isDragging = false;
	bool musicDayLaunched = false;
	bool musicNightLaunched = false;
	bool musicDeathLaunched = false;
	bool sonActif = true;

	//Textures
	sf::Texture backgroundDay;
	sf::Texture backgroundNight;
	sf::Texture texturePerso;
	sf::Texture persoTriste;
	sf::Texture persoFatigue;
	sf::Texture persoDormir;
	sf::Texture persoMalade;
	sf::Texture persoHappy;
	sf::Texture tombe;
	sf::Texture oeufIntact;
	sf::Texture oeufAlmCracked;
	sf::Texture oeufCracked;
	sf::Texture poop;
	sf::Texture dialogBox;
	sf::Texture cursor;
	sf::Texture alpha;
	sf::Texture jour;
	sf::Texture nuit;
	sf::Texture fruit;
	sf::Texture viande;
	sf::Texture muffin;
	sf::Texture stim;
	sf::Texture medkit;
	sf::Texture antidep;
	sf::Texture barreVie;
	sf::Texture barreFaim;
	sf::Texture barreNrj;
	sf::Texture barreJoie;
	sf::Texture menu;
	sf::Texture menuIG;
	sf::Texture options;
	sf::Texture checkmark;

	backgroundDay.loadFromFile("background01.png");
	backgroundNight.loadFromFile("background02.png");
	texturePerso.loadFromFile("Poupon.png");
	persoTriste.loadFromFile("fox_sad.png");
	persoFatigue.loadFromFile("fox_tired.png");
	persoDormir.loadFromFile("fox_sleep.png");
	persoMalade.loadFromFile("fox_sick.png");
	persoHappy.loadFromFile("fox_excited.png");
	tombe.loadFromFile("Tombe.png");
	oeufIntact.loadFromFile("egg.png");
	oeufAlmCracked.loadFromFile("egg_almostcracked.png");
	oeufCracked.loadFromFile("egg_cracked.png");
	poop.loadFromFile("poop.png");
	cursor.loadFromFile("Cursor.png");
	jour.loadFromFile("Soleil.png");
	nuit.loadFromFile("Lune.png");
	fruit.loadFromFile("Fruit.png");
	viande.loadFromFile("Viande.png");
	muffin.loadFromFile("Biscuit.png");
	stim.loadFromFile("Stim.png");
	medkit.loadFromFile("Medkit.png");
	antidep.loadFromFile("Antidep.png");
	barreVie.loadFromFile("Healthbar.png");
	barreFaim.loadFromFile("HungryBar.png");
	barreNrj.loadFromFile("EnergyBar.png");
	barreJoie.loadFromFile("HappinessBar.png");
	menuIG.loadFromFile("GameMenuIG.png");
	options.loadFromFile("Options.png");
	checkmark.loadFromFile("checkmark.png");

	//Rectangles de sélection
	//Creature
	sf::IntRect rectSource(0, 0, 212, 185);
	sf::IntRect rectHappy(0, 0, 188, 185);
	sf::IntRect rectOtherEmotion(0, 0, 263, 185);
	sf::IntRect rectOeuf(0, 0, 193, 231);
	sf::IntRect rectTombe(0, 0, 160, 212);
	//Curseur
	sf::IntRect rectCursor(0, 0, 32, 38);
	//Nourriture/Medicament
	sf::IntRect selectBox(0, 0, 50, 50);
	sf::IntRect rectFruit(0, 0, 50, 41);	//Marche aussi pour la viande
	sf::IntRect rectMuffin(0, 0, 50, 45);
	sf::IntRect rectMedkit(0, 0, 50, 38);
	sf::IntRect daynight(0, 0, 100, 100);
	//Barres
	sf::IntRect rectBarVie(0, 0, int(169 * Bestiole.getPV() / Bestiole.getPVMax()), 16);
	sf::IntRect rectBarFaim(0, 0, int(169 * Bestiole.getFaim() / Bestiole.getFaimMax()), 16);
	sf::IntRect rectBarNrj(0, 0, int(169 * Bestiole.getEnergie() / Bestiole.getEnergieMax()), 16);
	sf::IntRect rectBarJoie(0, 0, int(169 * Bestiole.getJoie() / Bestiole.getJoieMax()), 16);
	//UI
	sf::IntRect rectMainMenu(0, 0, 340, 440);
	sf::IntRect rectOptions(0, 0, 440, 340);
	sf::IntRect rectBoutons(0, 0, 180, 25);
	sf::IntRect rectCheck(0, 0, 36, 36);
	sf::IntRect rectValider(0, 0, 138, 24);

	sf::IntRect rectPoop(0, 0, 80, 62);

	//Sprite Background
	sf::Sprite backgroundD(backgroundDay);
	sf::Sprite backgroundN(backgroundNight);
	sf::Sprite spriteSoleil(jour, daynight);
	sf::Sprite spriteLune(nuit, daynight);

	//Sprite Bestiole
	sf::Sprite spritePerso(texturePerso, rectSource);
	sf::Sprite spritePersoFatigue(persoFatigue, rectOtherEmotion);
	sf::Sprite spritePersoDeprime(persoTriste, rectOtherEmotion);
	sf::Sprite spritePersoDodo(persoDormir, rectOtherEmotion);
	sf::Sprite spritePersoHappy(persoHappy, rectHappy);
	sf::Sprite spritePersoSick(persoMalade, rectOtherEmotion);
	sf::Sprite spriteTombe(tombe, rectTombe);
	sf::Sprite spriteOeuf(oeufIntact, rectOeuf);
	sf::Sprite spritePoop(poop, rectPoop);

	//Sprites interface
	sf::Sprite spriteCursor(cursor, rectCursor);
	sf::Sprite spriteFruit(fruit, rectFruit);
	sf::Sprite spriteViande(viande, rectFruit);
	sf::Sprite spriteMuffin(muffin, rectMuffin);
	sf::Sprite spriteStim(stim, selectBox);
	sf::Sprite spriteMedkit(medkit, rectMedkit);
	sf::Sprite spriteAntidep(antidep, selectBox);
	sf::Sprite spritePvBar(barreVie, rectBarVie);
	sf::Sprite spriteHungryBar(barreFaim, rectBarFaim);
	sf::Sprite spriteEnergyBar(barreNrj, rectBarNrj);
	sf::Sprite spriteJoieBar(barreJoie, rectBarJoie);

	sf::Sprite spriteMenuIG(menuIG, rectMainMenu);
	sf::Sprite spriteOptions(options, rectOptions);
	sf::Sprite spriteCheckmarkBox(alpha, rectCheck);
	spriteCheckmarkBox.setColor(sf::Color::Transparent);
	sf::Sprite spriteCheckmarkSon(checkmark, rectCheck);
	sf::Sprite spriteCheckmarkDifficulte(checkmark, rectCheck);
	sf::Sprite spriteValider(alpha, rectValider);
	spriteValider.setColor(sf::Color::Transparent);
	sf::Sprite spriteBoutons(alpha, rectBoutons);
	spriteBoutons.setColor(sf::Color::Transparent);
	sf::Sprite spriteSelection(alpha, selectBox);
	spriteSelection.setColor(sf::Color::Transparent);
	//création vector de sprites de sélection
	vector<sf::Sprite> casesSelection;
	for (int i = 1; i <= 10; i++)
	{
		casesSelection.push_back(spriteSelection);
	}
	//Création vector de sprites boutons
	vector<sf::Sprite> boutonsMenu;
	for (int j = 0; j <= 5; j++)
	{
		boutonsMenu.push_back(spriteBoutons);
	}

	//Coordonnées
	sf::Vector2i posSouris;
	//Coordonnées bestiole
	spritePerso.setPosition(200, 460);
	spritePersoFatigue.setPosition(200, 460);
	spritePersoDeprime.setPosition(200, 460);
	spritePersoDodo.setPosition(200, 460);
	spritePersoHappy.setPosition(200, 460);
	spritePersoSick.setPosition(200, 460);
	spriteTombe.setPosition(220, 418);
	spriteOeuf.setPosition(200, 400);
	//Caca
	spritePoop.setPosition(80, 560);

	//Coordonnées UI
	spriteSoleil.setPosition(460, 10);
	spriteLune.setPosition(460, 10);
	//Barres
	spritePvBar.setPosition(74, 7);
	spriteHungryBar.setPosition(74, 33);
	spriteEnergyBar.setPosition(73, 59);
	spriteJoieBar.setPosition(73, 85);

	//Dans le menu
	spriteMenuIG.setPosition(162, 180);
	spriteOptions.setPosition(112, 230);
	spriteCheckmarkBox.setPosition(339, 296);
	spriteCheckmarkSon.setPosition(339, 296);
	spriteCheckmarkDifficulte.setPosition(339, 383);
	spriteValider.setPosition(279, 484);

	//Boutons menu ig/main
	boutonsMenu[0].setPosition(240, 285);		//Nouvelle partie / Sauvegarder
	boutonsMenu[1].setPosition(240, 342);		//Charger
	boutonsMenu[2].setPosition(240, 400);		//Options
	boutonsMenu[3].setPosition(240, 460);		//Reprendre
	boutonsMenu[4].setPosition(240, 536);		//Quitter

	//Boutons Interface
	casesSelection[0].setPosition(30, 710);	//Bouton Menu
	spriteFruit.setPosition(110, 686);			//Fraise
	spriteViande.setPosition(180, 690);			//Viande
	spriteMuffin.setPosition(247, 685);			//Muffin	
	spriteStim.setPosition(315, 680);			//Stim
	spriteMedkit.setPosition(385, 690);			//Medkit
	spriteAntidep.setPosition(452, 685);		//Anti Dep
	casesSelection[7].setPosition(280, 740);	//Douche
	casesSelection[8].setPosition(565, 680);	//Soleil
	casesSelection[9].setPosition(565, 742);	//Lune
	//Limitation du framerate
	window.setFramerateLimit(60);
	//Curseur visible ou non
	window.setMouseCursorVisible(false);

	//Police de caractère et texte
	Bestiole.setNom("Starfox");

	//Creation horloge interne
	sf::Clock clock;
	float elapsed = 0;

	//Sons
	//Craquement oeuf
	sf::Sound eggCrack;
	sf::SoundBuffer bufferEgg;
	bufferEgg.loadFromFile("Crack.wav");
	eggCrack.setBuffer(bufferEgg);

	//Ambiance jour
	sf::Sound day;
	sf::SoundBuffer bufferDay;
	bufferDay.loadFromFile("Jour.wav");
	day.setBuffer(bufferDay);
	day.setLoop(true);

	//Ambiance nuit
	sf::Sound night;
	sf::SoundBuffer bufferNight;
	bufferNight.loadFromFile("Nuit.wav");
	night.setBuffer(bufferNight);
	night.setLoop(true);

	//DARKNESS my old friend...
	sf::Sound darkness;
	sf::SoundBuffer bufferDarkness;
	bufferDarkness.loadFromFile("Darkness.ogg");
	darkness.setBuffer(bufferDarkness);
	darkness.setLoop(true);

	while (window.isOpen())
	{
		//Creation event catcher
		sf::Event event;

		while (window.pollEvent(event))

		{
			//On récupère la position de la souris dans la fenêtre
			spriteCursor.setPosition((sf::Vector2f)sf::Mouse::getPosition(window));

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			//On clique sur un bouton pour ouvrir le menu, on fait échap pour le refermer
			if (onMenu == false && ((casesSelection[0].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))))
			{
				onMenu = true;
			}
			if (onMenu == true && ((event.type == event.KeyReleased && event.key.code == sf::Keyboard::Escape) || (boutonsMenu[3].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)))
			{
				onMenu = false;
			}

			//Dans le menu :
			if (onMenu == true)
			{
				if ((boutonsMenu[0].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
				{
					save(Bestiole);
				}
				else if ((boutonsMenu[1].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
				{

					window.close();
					day.stop();
					night.stop();
					jouer(load());
					onMenu = false;

				}
				else if ((boutonsMenu[4].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
				{
					window.close();
				}
				else if ((boutonsMenu[2].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
				{
					onOptions = true;
				}
			}

			if ((onOptions == true && sonActif == true) && (spriteCheckmarkBox.getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
			{
				sonActif = false;
			}
			else if ((onOptions == true && sonActif == false) && (spriteCheckmarkBox.getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
			{
				sonActif = true;
				day.play();
				night.play();
				eggCrack.play();
			}
			else if ((spriteValider.getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
			{
				onOptions = false;
			}

			//Clics sur l'oeuf pour le casser
			if ((onMenu == false || onOptions == false) && (Bestiole.getStade() == oeuf && (spriteCursor.getGlobalBounds().intersects(spriteOeuf.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))))
			{
				if (sonActif == true)
				{
					//Tant que le compter de clic est différent de 6 on joue le son de coquille cassée
					eggCrack.play();

					//Quand le compteur arrive à 6,  on charge le son Pop
					if (Bestiole.compteurClic == 5)
					{
						bufferEgg.loadFromFile("Pop.wav");
						eggCrack.setBuffer(bufferEgg);
						eggCrack.play();
					}
				}

				Bestiole.compteurClic++;
			}

			//Donner à manger, on redessine les barres de vie/faim/joie en fonction de la nourriture donnée
			if (Bestiole.enVie == true)
			{
				//Fruit
				if (spriteFruit.getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isDragging == false)
				{
					spriteFruit.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
					isDragging = true;
				}
				else if ((event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) && spriteFruit.getGlobalBounds().intersects(spritePerso.getGlobalBounds()))
				{
					Bestiole.donnerAManger(Repas.fruit, Bestiole);
					rectBarVie.width = int(169 * Bestiole.getPV() / Bestiole.getPVMax());
					spritePvBar.setTextureRect(rectBarVie);
					rectBarFaim.width = int(169 * Bestiole.getFaim() / Bestiole.getFaimMax());
					spriteHungryBar.setTextureRect(rectBarFaim);
					rectBarJoie.width = int(169 * Bestiole.getJoie() / Bestiole.getJoieMax());
					spriteJoieBar.setTextureRect(rectBarJoie);
					spriteFruit.setPosition(110, 686);
				}

				//Viande
				if (spriteViande.getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isDragging == false)
				{
					spriteViande.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
					isDragging = true;
					Repas.viande;
				}
				else if ((event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) && spriteViande.getGlobalBounds().intersects(spritePerso.getGlobalBounds()))
				{
					Bestiole.donnerAManger(Repas.viande, Bestiole);
					rectBarVie.width = int(169 * Bestiole.getPV() / Bestiole.getPVMax());
					spritePvBar.setTextureRect(rectBarVie);
					rectBarFaim.width = int(169 * Bestiole.getFaim() / Bestiole.getFaimMax());
					spriteHungryBar.setTextureRect(rectBarFaim);
					rectBarJoie.width = int(169 * Bestiole.getJoie() / Bestiole.getJoieMax());
					spriteJoieBar.setTextureRect(rectBarJoie);
					spriteViande.setPosition(180, 690);
				}
				//Muffin
				if (spriteMuffin.getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isDragging == false)
				{
					spriteMuffin.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
					isDragging = true;
				}
				else if ((event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) && spriteMuffin.getGlobalBounds().intersects(spritePerso.getGlobalBounds()))
				{
					Bestiole.donnerAManger(Repas.viande, Bestiole);
					rectBarVie.width = int(169 * Bestiole.getPV() / Bestiole.getPVMax());
					spritePvBar.setTextureRect(rectBarVie);
					rectBarFaim.width = int(169 * Bestiole.getFaim() / Bestiole.getFaimMax());
					spriteHungryBar.setTextureRect(rectBarFaim);
					rectBarJoie.width = int(169 * Bestiole.getJoie() / Bestiole.getJoieMax());
					spriteJoieBar.setTextureRect(rectBarJoie);
					spriteMuffin.setPosition(247, 685);
				}


				//Les médicaments pour soigner les statuts
					//Stimulant
				if (spriteStim.getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isDragging == false)
				{
					spriteStim.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
					isDragging = true;
				}
				else if ((event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) && spriteStim.getGlobalBounds().intersects(spritePerso.getGlobalBounds()))
				{
					Bestiole.soigner(Soin.stimulant, Bestiole);
					spriteStim.setPosition(315, 680);
					rectBarNrj.width = int(169 * Bestiole.getEnergie() / Bestiole.getEnergieMax());
					spriteEnergyBar.setTextureRect(rectBarNrj);
				}
				//Medkit
				if (spriteMedkit.getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isDragging == false)
				{
					spriteMedkit.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
					isDragging = true;
				}
				else if ((event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) && spriteMedkit.getGlobalBounds().intersects(spritePerso.getGlobalBounds()))
				{
					Bestiole.soigner(Soin.hyperproteine, Bestiole);
					spriteMedkit.setPosition(385, 690);
					rectBarVie.width = int(169 * Bestiole.getPV() / Bestiole.getPVMax());
					spritePvBar.setTextureRect(rectBarVie);

				}
				//Antidep
				if (spriteAntidep.getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isDragging == false)
				{
					spriteAntidep.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
					isDragging = true;
				}
				else if ((event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) && spriteAntidep.getGlobalBounds().intersects(spritePerso.getGlobalBounds()))
				{
					Bestiole.soigner(Soin.antidepresseur, Bestiole);
					spriteAntidep.setPosition(452, 685);
					rectBarJoie.width = int(169 * Bestiole.getJoie() / Bestiole.getJoieMax());
					spriteJoieBar.setTextureRect(rectBarJoie);
				}
				/*Je suis entrain de glisser-déposer*/
				else
				{
					isDragging = false;
				}


				//Laver
				if (casesSelection[7].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
				{
					Bestiole.laver();
					rectBarJoie.width = int(169 * Bestiole.getJoie() / Bestiole.getJoieMax());
					spriteJoieBar.setTextureRect(rectBarJoie);
				}

				//On détermine quel stade de la journée on se trouve, déclenche le statut dormir ou non
				//Jour
				if (casesSelection[8].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
				{
					isDay = true;
				}

				//Nuit
				if (casesSelection[9].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
				{
					isDay = false;
				}
			}
			//Sons d'ambiance
			if (sonActif == true)
			{
				if (isDay == true && musicDayLaunched == false)
				{
					night.stop();
					day.play();
					musicNightLaunched = false;
					musicDayLaunched = true;
				}
				else if (isDay == false && musicNightLaunched == false)
				{
					day.stop();
					night.play();
					musicDayLaunched = false;
					musicNightLaunched = true;
				}
				
				if (Bestiole.enVie==false)
				{
					day.stop();
					night.stop();
				}

			}
			else if (sonActif == false)
			{
				night.stop();
				day.stop();
				eggCrack.stop();

			}
		}

		//Logique Creature

			// Horloge interne et attributs diminuant en fonction du temps
		elapsed += clock.restart().asMilliseconds();

		//Si la nuit est active
		if (Bestiole.enVie == true && elapsed >= 3000 && onMenu == false && isDay == false && Bestiole.getStade() == enfant)
		{
			//Faim
			Bestiole.setFaim(Bestiole.getFaim() - 2 * difficulte);
			rectBarFaim.width = int(169 * Bestiole.getFaim() / Bestiole.getFaimMax());
			spriteHungryBar.setTextureRect(rectBarFaim);
			//Energie
			Bestiole.setEnergie(Bestiole.getEnergie() + 7);
			rectBarNrj.width = int(169 * Bestiole.getEnergie() / Bestiole.getEnergieMax());
			spriteEnergyBar.setTextureRect(rectBarNrj);

			//Gestion d'erreur si les barres trop "trop pleines"
			//Energie
			if (Bestiole.getEnergie() >= Bestiole.getEnergieMax())
			{
				Bestiole.setEnergie(Bestiole.getEnergieMax());
				rectBarNrj.width = int(169 * Bestiole.getEnergie() / Bestiole.getEnergieMax());
				spriteEnergyBar.setTextureRect(rectBarNrj);
			}
			//Faim
			if (Bestiole.getFaim() >= Bestiole.getFaimMax())
			{
				Bestiole.setFaim(Bestiole.getFaimMax());
				rectBarFaim.width = int(169 * Bestiole.getFaim() / Bestiole.getFaimMax());
				spriteHungryBar.setTextureRect(rectBarFaim);
			}
			//Joie
			if (Bestiole.getJoie() >= Bestiole.getJoieMax())
			{
				Bestiole.setJoie(Bestiole.getJoieMax());
				rectBarJoie.width = int(169 * Bestiole.getJoie() / Bestiole.getJoieMax());
				spriteJoieBar.setTextureRect(rectBarJoie);
			}
			//Gstion d'erreur si les barres sont "trop vides"
			//Energie
			if (Bestiole.getEnergie() <= 0)
			{
				Bestiole.setEnergie(0);
			}
			//Faim
			if (Bestiole.getFaim() <= 0)
			{
				Bestiole.setFaim(0);
			}
			//Joie
			if (Bestiole.getJoie() <= 0)
			{
				Bestiole.setJoie(0);
			}

			elapsed = 0;
		}
		//Si c'est le jour
		else if (Bestiole.enVie == true && elapsed >= 3000 && onMenu == false && isDay == true && Bestiole.getStade() == enfant)
		{
			if (Bestiole.getFaim() != 0)
			{
				Bestiole.setFaim(Bestiole.getFaim() - 4 * difficulte);
				rectBarFaim.width = int(169 * Bestiole.getFaim() / Bestiole.getFaimMax());
				spriteHungryBar.setTextureRect(rectBarFaim);
			}
			if (Bestiole.getEnergie() != 0)
			{
				Bestiole.setEnergie(Bestiole.getEnergie() - 3 * difficulte);
				rectBarNrj.width = int(169 * Bestiole.getEnergie() / Bestiole.getEnergieMax());
				spriteEnergyBar.setTextureRect(rectBarNrj);
			}
			if (Bestiole.getJoie() != 0)
			{
				Bestiole.setJoie(Bestiole.getJoie() - 5 * difficulte);
				rectBarJoie.width = int(169 * Bestiole.getJoie() / Bestiole.getJoieMax());
				spriteJoieBar.setTextureRect(rectBarJoie);
			}
			if (Bestiole.getPV() != 0 && (Bestiole.getFaim() <= 0 || Bestiole.getEnergie() <= 0 || Bestiole.getJoie() <= 0))
			{
				Bestiole.setPV(Bestiole.getPV() - 6 * difficulte);
				rectBarVie.width = int(169 * Bestiole.getPV() / Bestiole.getPVMax());
				spritePvBar.setTextureRect(rectBarVie);
			}

			//Gestion d'erreur si les barres trop "trop pleines"
				//Energie
			if (Bestiole.getEnergie() >= Bestiole.getEnergieMax())
			{
				Bestiole.setEnergie(Bestiole.getEnergieMax());
				rectBarNrj.width = int(169 * Bestiole.getEnergie() / Bestiole.getEnergieMax());
				spriteEnergyBar.setTextureRect(rectBarNrj);
			}
			//Faim
			if (Bestiole.getFaim() >= Bestiole.getFaimMax())
			{
				Bestiole.setFaim(Bestiole.getFaimMax());
				rectBarFaim.width = int(169 * Bestiole.getFaim() / Bestiole.getFaimMax());
				spriteHungryBar.setTextureRect(rectBarFaim);
			}
			//Joie
			if (Bestiole.getJoie() >= Bestiole.getJoieMax())
			{
				Bestiole.setJoie(Bestiole.getJoieMax());
				rectBarJoie.width = int(169 * Bestiole.getJoie() / Bestiole.getJoieMax());
				spriteJoieBar.setTextureRect(rectBarJoie);
			}
			//PV
			if (Bestiole.getPV() >= Bestiole.getPVMax())
			{
				Bestiole.setPV(Bestiole.getPVMax());
				rectBarVie.width = int(169 * Bestiole.getPV() / Bestiole.getPVMax());
				spritePvBar.setTextureRect(rectBarVie);
			}
			//Gstion d'erreur si les barres sont "trop vides"
				//Energie
			if (Bestiole.getEnergie() <= 0)
			{
				Bestiole.setEnergie(0);
			}
			//Faim
			if (Bestiole.getFaim() <= 0)
			{
				Bestiole.setFaim(0);
			}
			//Joie
			if (Bestiole.getJoie() <= 0)
			{
				Bestiole.setJoie(0);
			}
			//PV
			if (Bestiole.getPV() <= 0)
			{
				Bestiole.setPV(0);
				Bestiole.setJoie(0);
				Bestiole.setFaim(0);
				Bestiole.setEnergie(0);
			}
			elapsed = 0;
		}

		if (Bestiole.getNbNourris() >= 2)
		{
			Bestiole.faireCaca();
		}

		/*Ici je détermine quel est le statut de la créature selon ses attributs et la quantité de hp/faim/joie/énergie qu'elle possède*/

		//Statut deprime
		if (Bestiole.getJoie() <= 20 && Bestiole.getStatut() != malade)
		{
			Bestiole.setStatut(deprime);
		}
		//Statut extenue
		else if (Bestiole.getEnergie() <= 20)
		{
			Bestiole.setStatut(extenue);
		}
		//Statut heureux
		else if ((Bestiole.getJoie() >= 70 && Bestiole.getFaim() >= 70 && Bestiole.getEnergie() >= 70) && Bestiole.getStatut() != malade && isDay == true)
		{
			Bestiole.setStatut(heureux);
		}
		else if (Bestiole.getNbCacas() >= 3 || Bestiole.getFaim() == 0 || Bestiole.getJoie() == 0 || Bestiole.getEnergie() == 0)
		{
			Bestiole.setStatut(malade);
		}
		//Statut dort
		else if (isDay == false)
		{
			Bestiole.setStatut(dort);
		}
		else
		{
			Bestiole.setStatut(idle);
		}

		//Créature décédée :'(
		if (Bestiole.getPV() <= 0)
		{
			Bestiole.enVie = false;
		}
		if (Bestiole.enVie == false && Bestiole.getStade() == enfant && musicDeathLaunched == false)
		{
				darkness.play();
				musicDeathLaunched = true;
		}

		/*Par manque de temps, je n'exploiterai pas le gain de niveau et d'évolution*/
		////Gain niveau
		//if (Bestiole.getExpActuel() == Bestiole.getExpMax())
		//{
		//	Bestiole.gagnerNiveau(Bestiole);
		//}
		////Evolution
		//else if (Bestiole.getNiveau() == 3)
		//{
		//	Bestiole.evoluer(Bestiole, enfant);
		//}

		window.clear();

		//UI
		if (isDay == true)
		{
			window.clear();
			window.draw(backgroundD);
			window.draw(spriteSoleil);
		}
		if (isDay == false)
		{
			window.clear();
			window.draw(backgroundN);
			window.draw(spriteLune);

		}
		//Je dessine les cases de l'UI
		for (unsigned int i = 0; i < casesSelection.size(); i++)
		{
			window.draw(casesSelection[i]);
		}
		//Crea
			//Si le stade est oeuf :
		if (Bestiole.getStade() == oeuf)
		{
			switch (Bestiole.compteurClic)
			{
			case 0:
			case 1:
			case 2:
				spriteOeuf.setTexture(oeufIntact);
				window.draw(spriteOeuf);
				break;
			case 3:
			case 4:
				spriteOeuf.setTexture(oeufAlmCracked);
				window.draw(spriteOeuf);
				break;
			case 5:
				spriteOeuf.setTexture(oeufCracked);
				window.draw(spriteOeuf);
				break;
			case 6:
				Bestiole.setStade(enfant);
				break;
			}
		}
		//Si le stade est enfant
		if (Bestiole.getStade() == enfant && Bestiole.enVie == true)
		{
			//Selon le statut de la créature, on dessine tel ou tel sprite
			switch (Bestiole.getStatut())
			{
			case idle:
				window.draw(spritePerso);
				break;
			case extenue:
				window.draw(spritePersoFatigue);
				break;
			case deprime:
				window.draw(spritePersoDeprime);
				break;
			case heureux:
				window.draw(spritePersoHappy);
				break;
			case dort:
				window.draw(spritePersoDodo);
				break;
			case malade:
				window.draw(spritePersoSick);
				break;
			}
		}
		//On dessine le sprite de caca
		if (Bestiole.getNbCacas() >= 1 && Bestiole.enVie == true)
		{
			window.draw(spritePoop);
		}
		if (Bestiole.enVie == false)
		{
			window.draw(spriteTombe);
		}


		//Aliment & Medicament : on dessine les icones de l'interface
		window.draw(spriteStim);
		window.draw(spriteMedkit);
		window.draw(spriteAntidep);
		window.draw(spriteFruit);
		window.draw(spriteViande);
		window.draw(spriteMuffin);
		window.draw(spritePvBar);
		window.draw(spriteEnergyBar);
		window.draw(spriteHungryBar);
		window.draw(spriteJoieBar);

		//Je trace les boutons d'intéraction quand je suis dans le menu
		if (onMenu == true)
		{
			window.draw(spriteMenuIG);
			window.draw(boutonsMenu[0]);
			window.draw(boutonsMenu[1]);
			window.draw(boutonsMenu[2]);
			window.draw(boutonsMenu[3]);
			window.draw(boutonsMenu[4]);
		}
		//Si je suis dans le menu des options

		if (onOptions == true)
		{
			onMenu = false;
			window.draw(spriteOptions);
			window.draw(spriteCheckmarkBox);
			window.draw(spriteCheckmarkDifficulte);
			window.draw(spriteValider);
		}
		if (sonActif == true && onOptions == true)
		{
			window.draw(spriteCheckmarkSon);
		}
		//Curseur
		window.draw(spriteCursor);
		window.display();
	}
}