#include "Jeu.h"


using namespace std;

Jeu::Jeu()
{
}

Jeu::~Jeu()
{
}


//void Jeu::chooseState(Jeu::gameState)
//{
//	switch (gameState)
//	{
//	case game: 
//			jouer();
//		break;
//	case menu:
//			mainMenu();
//	default:
//		break;
//	}
//}


void Jeu::jouer()
{
	sf::RenderWindow window(sf::VideoMode(665, 800), "What does the fox say ?");

	//Creation créature
	Creature Bestiole;
	//Creation nourriture
	Nourriture Repas;
	//Creation medicament
	Medicament Soin;
	bool isDay = true;
	bool isDragging = false;


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
	spriteOeuf.setPosition(100, 380);
	
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
	//On dessine un curseur de souris perso à la position du curseur.
	/*spriteCursor.setTextureRect(rectCursor);*/

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
			if (casesSelection[0].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				onMenu = true;
			}
			if ((event.type == event.KeyReleased && event.key.code == sf::Keyboard::Escape) || (boutonsMenu[3].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
			{
				onMenu = false;
			}

			//Dans le menu :
			if (onMenu == true)
			{
				//if ((boutonsMenu[0].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
				//{
				//	save(Bestiole);
				//}
				//else if ((boutonsMenu[1].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
				//{
				//	load(Bestiole);
				//}
				if ((boutonsMenu[2].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
				{
					onOptions = true;
				}
				else
				{
					onOptions = false;
				}
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
				/*Mettre ici le fait de nettoyer le caca et enlever le statut malade de la créature*/
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

		if (elapsed >= 3000 && onMenu==false)
		{
			/*Cette partie du code bug et ça me gonfle,  dès que je met 3 if ou alors juste la partie "Joie" , l'ensemble déconne et les barres se figent : problème de timer ? overload de mémoire ?*/
			if (isDay == true)
			{
				//Faim
				Bestiole.setFaim(Bestiole.getFaim() - 4);
				rectBarFaim.width = int(169 * Bestiole.getFaim() / Bestiole.getFaimMax());
				spriteHungryBar.setTextureRect(rectBarFaim);

				//Energie
				Bestiole.setEnergie(Bestiole.getEnergie() - 3);
				rectBarNrj.width = int(169 * Bestiole.getEnergie() / Bestiole.getEnergieMax());
				spriteEnergyBar.setTextureRect(rectBarNrj);

				//Joie
				Bestiole.setJoie(Bestiole.getJoie() - 2);
				rectBarJoie.width = int(169 * Bestiole.getJoie() / Bestiole.getJoieMax());
				spriteJoieBar.setTextureRect(rectBarJoie);
			}
			else if (isDay == false)
			{
				//Faim
				Bestiole.setFaim(Bestiole.getFaim() - 1);
				rectBarFaim.width = int(169 * Bestiole.getFaim() / Bestiole.getFaimMax());
				spriteHungryBar.setTextureRect(rectBarFaim);

				//Energie
				Bestiole.setEnergie(Bestiole.getEnergie() + 5);
				rectBarNrj.width = int(169 * Bestiole.getEnergie() / Bestiole.getEnergieMax());
				spriteEnergyBar.setTextureRect(rectBarNrj);

				//Joie
				Bestiole.setJoie(Bestiole.getJoie() + 2);
				rectBarJoie.width = int(169 * Bestiole.getJoie() / Bestiole.getJoieMax());
				spriteJoieBar.setTextureRect(rectBarJoie);
			}

			//Gestion erreur si nombre supérieur à la quantité max
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
			/*Faire ICI la gestion des erreur quand les barres atteignent une valeur "négative" en les mettant à 0*/
			

			elapsed = 0;



			//if (Bestiole.getFaim() >= 0)
			//{
			//	Bestiole.setFaim(Bestiole.getFaim() - 4);
			//	rectBarFaim.width = int(169 * Bestiole.getFaim() / Bestiole.getFaimMax());
			//	spriteHungryBar.setTextureRect(rectBarFaim);
			//}
			//else if ((Bestiole.getFaim() >= 0) && isDay == false)
			//{
			//	Bestiole.setFaim(Bestiole.getFaim() - 1);
			//	rectBarFaim.width = int(169 * Bestiole.getFaim() / Bestiole.getFaimMax());
			//	spriteHungryBar.setTextureRect(rectBarFaim);
			

			////Energie
			//if (Bestiole.getEnergie() >= 0)
			//{
			//	Bestiole.setEnergie(Bestiole.getEnergie() - 3);
			//	rectBarNrj.width = int(169 * Bestiole.getEnergie() / Bestiole.getEnergieMax());
			//	spriteEnergyBar.setTextureRect(rectBarNrj);
			//}
			//else if ((Bestiole.getEnergie()<=Bestiole.getEnergieMax()) && isDay == false)
			//{
			//	Bestiole.setEnergie(Bestiole.getEnergie() + 5);
			//	rectBarNrj.width = int(169 * Bestiole.getEnergie() / Bestiole.getEnergieMax());
			//	spriteEnergyBar.setTextureRect(rectBarNrj);
			//}

			////Joie
			//if (Bestiole.getJoie()>= 0)
			//{
			//	Bestiole.setJoie(Bestiole.getJoie() - 3);
			//	rectBarJoie.width = int(169 * Bestiole.getJoie() / Bestiole.getJoieMax());
			//	spriteJoieBar.setTextureRect(rectBarJoie);
			//}
			//else if ((Bestiole.getJoie() <= Bestiole.getJoieMax()) && isDay == false)
			//{
			//	Bestiole.setJoie(Bestiole.getJoie() + 2);
			//	rectBarJoie.width = int(169 * Bestiole.getJoie() / Bestiole.getJoieMax());
			//	spriteJoieBar.setTextureRect(rectBarJoie);
			//}
		}

		//Faire ses besoins
		if (Bestiole.getNbNourris() == 3)
		{
			Bestiole.faireCaca();
			/*intégrer la création de sprite et l'apparition de caca*/
		}

		/*Ici je détermine quel est le statut de la créature selon ses attributs et la quantité de hp/faim/joie/énergie qu'elle possède*/

		//Statut deprime
		if ((Bestiole.getNbCacas() >= 3) || (Bestiole.getJoie()<=20))
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
		//Statut dort
		else if (isDay == false)
		{
			Bestiole.setStatut(dort);
		}
		else
		{
			Bestiole.setStatut(idle);
		}

		
		
		/*Par manque de temps, je n'exploiterai pas le gain de niveau et d'évolution*/
		//Gain niveau
		if (Bestiole.getExpActuel() == Bestiole.getExpMax())
		{
			Bestiole.gagnerNiveau(Bestiole);
		}
		//Evolution
		else if (Bestiole.getNiveau() == 3)
		{
			Bestiole.evoluer(Bestiole, enfant);
		}



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
		if (Bestiole.enVie = true)
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

