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
		cout << errmsg << endl;
		return false;
	}
	else
	{
		cout << "BDD remplie !"<< endl;
		return true;
	}
}

bool Jeu::save(int pv, int faim, int nrj, int joie, int nbCaca, int nbNourris)
{
	char bpv[10];
	char bfaim[10];
	char bnrj[10];
	char bjoie[10];
	char bnbCaca[10];
	char bnbNourris[10];
	sprintf_s(bpv, "%d", pv);
	sprintf_s(bfaim, "%d", faim);
	sprintf_s(bnrj, "%d", nrj);
	sprintf_s(bjoie, "%d", joie);
	sprintf_s(bnbCaca, "%d", nbCaca);
	sprintf_s(bnbNourris, "%d", nbNourris);


	string query = "INSERT INTO Creature VALUES('";
	query += bpv;
	query += ",";
	query += bfaim;
	query += ",";
	query += bnrj;
	query += ",";
	query += bjoie;
	query += ",";
	query += bnbCaca;
	query += ",";
	query += bnbNourris;
	query += ")";

	return executeQuery(query);
}


vector<Creature*>* Jeu::load()
{
	string query = "SELECT rowid, * FROM Creature";
	vector<Creature*>* crea = new vector<Creature*>;
	int i;

	sqlite3_stmt * stmt;
	sqlite3_prepare_v2(db, query.c_str(), strlen(query.c_str()) + 1, &stmt, NULL);

	do {
		i = sqlite3_step(stmt);
		if (i == SQLITE_ROW)
		{
			Creature * creature = new Creature();
			crea->push_back(creature);

			
			creature->setPV(sqlite3_column_int(stmt, 1));
			creature->setFaim(sqlite3_column_int(stmt, 2));
			creature->setEnergie(sqlite3_column_int(stmt, 3));
			creature->setJoie(sqlite3_column_int(stmt, 4));
			creature->setNbCacas(sqlite3_column_int(stmt, 5));
			creature->setNbNourris(sqlite3_column_int(stmt, 6));
		}
	} while (i == SQLITE_ROW);

	return crea;
}



void Jeu::chooseState(Jeu tamago, Jeu::gameState state)
{
	switch (state)
	{
	case game:
		tamago.jouer();
		break;
	case menu:
		tamago.titlescreen();
		break;
	default:
		break;
	}
}

void Jeu::titlescreen()
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
				jouer();
			}
			
		}


		window.clear();

		window.draw(boutonsMenu[0]);
		window.draw(boutonsMenu[3]);

		window.draw(spriteBackgroundTitre);
		window.draw(spriteCursorTitre);

		window.display();
	}
}

void Jeu::jouer()
{
	sf::RenderWindow window(sf::VideoMode(665, 800), "What does the fox say ?");

	//Creation créature
	Creature Bestiole;
	Bestiole.setStade(oeuf);
	//Creation nourriture
	Nourriture Repas;
	//Creation medicament
	Medicament Soin;
	//Variables globales
	bool isDay = true;
	bool isDragging = false;
	int compteurClic = 0;

	//Textures
	sf::Texture backgroundDay;
	sf::Texture backgroundNight;
	sf::Texture texturePerso;
	sf::Texture persoTriste;
	sf::Texture persoFatigue;
	sf::Texture persoDormir;
	sf::Texture persoMalade;
	sf::Texture persoHappy;
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
	sf::Texture chargement;

	backgroundDay.loadFromFile("background1.png");
	backgroundNight.loadFromFile("background2.png");
	texturePerso.loadFromFile("Poupon.png");
	persoTriste.loadFromFile("fox_sad.png");
	persoFatigue.loadFromFile("fox_tired.png");
	persoDormir.loadFromFile("fox_sleep.png");
	persoMalade.loadFromFile("fox_sick.png");
	persoHappy.loadFromFile("fox_excited.png");
	oeufIntact.loadFromFile("egg.png");
	oeufAlmCracked.loadFromFile("egg_almostcracked.png");
	oeufCracked.loadFromFile("egg_cracked.png");
	poop.loadFromFile("poop.png");
	dialogBox.loadFromFile("bubble.png");
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
	menu.loadFromFile("GameMenu.png");
	menuIG.loadFromFile("GameMenuIG.png");
	options.loadFromFile("Options.png");
	chargement.loadFromFile("Load.png");


	//Rectangles de sélection
	sf::IntRect rectSource(0, 0, 275, 240);
	sf::IntRect rectHappy(0, 0, 245, 240);
	sf::IntRect rectOtherEmotion(0, 0, 345, 240);
	sf::IntRect rectOeuf(0, 0, 250, 300);
	sf::IntRect rectCursor(0, 0, 32, 38);
	sf::IntRect selectBox(0, 0, 50, 50);
	sf::IntRect rectFruit(0, 0, 50, 41);	//Marche aussi pour la viande
	sf::IntRect rectMuffin(0, 0, 50, 45);
	sf::IntRect rectMedkit(0, 0, 50, 38);
	sf::IntRect daynight(0, 0, 100, 100);
	sf::IntRect rectBarVie(0, 0, int(169 * Bestiole.getPV() / Bestiole.getPVMax()), 16);
	sf::IntRect rectBarFaim(0, 0, int(169 * Bestiole.getFaim() / Bestiole.getFaimMax()), 16);
	sf::IntRect rectBarNrj(0, 0, int(169 * Bestiole.getEnergie() / Bestiole.getEnergieMax()), 16);
	sf::IntRect rectBarJoie(0, 0, int(169 * Bestiole.getJoie() / Bestiole.getJoieMax()), 16);
	sf::IntRect rectMainMenu(0, 0, 340, 440);
	sf::IntRect rectOptions(0, 0, 440, 340);    //Marche aussi pour ecran chargement
	sf::IntRect rectBoutons(0, 0, 180, 25);
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
	sf::Sprite spriteMainMenu(menu, rectMainMenu);
	sf::Sprite spriteMenuIG(menuIG, rectMainMenu);
	sf::Sprite spriteOptions(options, rectOptions);
	sf::Sprite spriteChargement(chargement, rectOptions);
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
	spritePerso.setPosition(100, 380);
	spritePersoFatigue.setPosition(100,380);
	spritePersoDeprime.setPosition(100, 380);
	spritePersoDodo.setPosition(100, 380);
	spritePersoHappy.setPosition(100, 380);
	spritePersoSick.setPosition(100, 380);
	spriteOeuf.setPosition(100, 320);
	spritePoop.setPosition(80, 560);
	
	//Coordonnées UI
	spriteSoleil.setPosition(460, 10);
	spriteLune.setPosition(460, 10);
	spritePvBar.setPosition(75, 6);
	spriteHungryBar.setPosition(75, 33);
	spriteEnergyBar.setPosition(74, 58);
	spriteJoieBar.setPosition(74, 86);
	spriteMainMenu.setPosition(162, 180);
	spriteMenuIG.setPosition(162, 180);
	spriteOptions.setPosition(112, 330);
	spriteChargement.setPosition(112, 330);
	//Boutons menu ig/main
	boutonsMenu[0].setPosition(240,285);	//Nouvelle partie / Sauvegarder
	boutonsMenu[1].setPosition(240,342);	//Charger
	boutonsMenu[2].setPosition(240,400);	//Options
	boutonsMenu[3].setPosition(240,460);	//Reprendre
	boutonsMenu[4].setPosition(240,536);	//Quitter

	//Boutons Interface
	casesSelection[0].setPosition(150, 710);
	casesSelection[1].setPosition(231, 685);
	spriteFruit.setPosition(231, 690);
	casesSelection[2].setPosition(308, 685);
	spriteViande.setPosition(308, 690);
	casesSelection[3].setPosition(386, 685);
	spriteMuffin.setPosition(386, 687);
	casesSelection[4].setPosition(231, 745);
	spriteStim.setPosition(231, 745);
	casesSelection[5].setPosition(308, 745);
	spriteMedkit.setPosition(308, 748);
	casesSelection[6].setPosition(386, 745);
	spriteAntidep.setPosition(386, 745);
	casesSelection[7].setPosition(478, 713);
	casesSelection[8].setPosition(575, 684);
	casesSelection[9].setPosition(575, 741);
	//Limitation du framerate
	window.setFramerateLimit(60);
	//Curseur visible ou non
	window.setMouseCursorVisible(false);

	//Police de caractère et texte
	sf::Font font;
	font.loadFromFile("Mak Dah.ttf");
	sf::Text nomCrea;
	nomCrea.setFont(font);
	nomCrea.setCharacterSize(36);
	nomCrea.setFillColor(sf::Color::Black);

	Bestiole.setNom("Starfox");
	nomCrea.setString(Bestiole.getNom());
	nomCrea.setPosition(482, 410);


	//Creation horloge interne
	sf::Clock clock;
	float elapsed=0;

	while (window.isOpen())
	{
		//Creation event catcher
		sf::Event event;

		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			spriteCursor.setPosition((sf::Vector2f)sf::Mouse::getPosition(window));

			//On clique sur un bouton pour ouvrir le menu, on fait échap pour le refermer
			if ( onMenu==false && ((casesSelection[0].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))))
			{
				onMenu = true;
			}
			if (onMenu==true &&  ((event.type == event.KeyReleased && event.key.code == sf::Keyboard::Escape) || (boutonsMenu[3].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)))
			{
				onMenu = false;
			}

			//Dans le menu :
			if (onMenu == true)
			{
				if ((boutonsMenu[0].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
				{
					save(Bestiole.getPV(), Bestiole.getFaim(), Bestiole.getEnergie(), Bestiole.getJoie(), Bestiole.getNbCacas(), Bestiole.getNbNourris());
				}
				else if ((boutonsMenu[1].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
				{
					load();
				}
				if ((boutonsMenu[2].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
				{
					onOptions = true;
				}
				else
				{
					onOptions = false;
				}
			}
			

			//Clics sur l'oeuf pour le casser
			if (Bestiole.getStade()==oeuf && (spriteCursor.getGlobalBounds().intersects(spriteOeuf.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)))
			{
				compteurClic++;
			}



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
				spriteFruit.setPosition(231, 690);
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
				spriteViande.setPosition(308, 690);
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
				spriteMuffin.setPosition(386, 687);
			}
			//Stimulant
			if (spriteStim.getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isDragging == false)
			{
				spriteStim.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				isDragging = true;
			}
			else if ((event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) && spriteStim.getGlobalBounds().intersects(spritePerso.getGlobalBounds()))
			{
				Bestiole.soigner(Soin.stimulant, Bestiole);
				spriteStim.setPosition(231, 745);
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
				spriteMedkit.setPosition(308, 748);
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
				spriteAntidep.setPosition(386, 745);
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

		//Logique Creature

		// Horloge interne et attributs diminuant en fonction du temps
		elapsed += clock.restart().asMilliseconds();

		if (Bestiole.enVie==true && elapsed >= 3000 && onMenu == false && isDay==false && Bestiole.getStade()==enfant)
		{
			//Faim
			Bestiole.setFaim(Bestiole.getFaim() - 2);
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
		else if (Bestiole.enVie == true && elapsed >= 3000 && onMenu == false && isDay == true && Bestiole.getStade() == enfant)
		{
			if (Bestiole.getFaim() != 0)
			{
				Bestiole.setFaim(Bestiole.getFaim() - 4);
				rectBarFaim.width = int(169 * Bestiole.getFaim() / Bestiole.getFaimMax());
				spriteHungryBar.setTextureRect(rectBarFaim);
			}
			if (Bestiole.getEnergie() != 0)
			{
				Bestiole.setEnergie(Bestiole.getEnergie() - 3);
				rectBarNrj.width = int(169 * Bestiole.getEnergie() / Bestiole.getEnergieMax());
				spriteEnergyBar.setTextureRect(rectBarNrj);
			}
			if (Bestiole.getJoie() != 0)
			{
				Bestiole.setJoie(Bestiole.getJoie() - 5);
				rectBarJoie.width = int(169 * Bestiole.getJoie() / Bestiole.getJoieMax());
				spriteJoieBar.setTextureRect(rectBarJoie);
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

		if (Bestiole.getNbNourris() >= 2)
		{
			Bestiole.faireCaca();
		}



		/*Ici je détermine quel est le statut de la créature selon ses attributs et la quantité de hp/faim/joie/énergie qu'elle possède*/

		//Statut deprime
		if (Bestiole.getJoie()<=20 && Bestiole.getStatut()!=malade)
		{
			Bestiole.setStatut(deprime);
		}
		//Statut extenue
		else if (Bestiole.getEnergie() <= 20)
		{
			Bestiole.setStatut(extenue);
		}
		//Statut heureux
		else if ((Bestiole.getJoie() >= 70 && Bestiole.getFaim() >= 70 && Bestiole.getEnergie() >= 70) && Bestiole.getStatut() != malade && isDay==true)
		{
			Bestiole.setStatut(heureux);
		}
		else if (Bestiole.getNbCacas() >= 3 || Bestiole.getFaim()==0 || Bestiole.getJoie() == 0 || Bestiole.getEnergie() == 0)
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
		//Statut malade
		//La perte de points de vie est lancée si la créature est malade
		if (Bestiole.getStatut() == malade)
		{
			if (elapsed >= 3000 && onMenu == false && isDay == true && Bestiole.getStade() == enfant && Bestiole.getPV()<=0)
			{
					Bestiole.setPV(Bestiole.getPV() - 7);
					rectBarVie.width = int(169 * Bestiole.getPV() / Bestiole.getPVMax());
					spritePvBar.setTextureRect(rectBarVie);
					if (Bestiole.getPV() <= 0)
					{
						Bestiole.setPV(0);
					}
			}
		}
		//Créature décédée :'(
		if (Bestiole.getPV() == 0)
		{
			Bestiole.enVie = false;
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
		window.draw(nomCrea);
		//Crea
		if (Bestiole.getStade() == oeuf)
		{
			switch (compteurClic)
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
		if (Bestiole.enVie = true && Bestiole.getStade()==enfant)
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
		
		if (Bestiole.getNbCacas()>=1)
		{
			window.draw(spritePoop);
		}

		//Aliment & Medicament
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
		else if (onMenu == true && onOptions == true)
		{
			window.draw(spriteMenuIG);
			window.draw(spriteOptions);
		}
		//Curseur
		window.draw(spriteCursor);
		window.display();
	}
}