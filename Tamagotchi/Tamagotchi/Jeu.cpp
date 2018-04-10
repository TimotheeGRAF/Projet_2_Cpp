#include "Jeu.h"
#include <iostream>
#include <vector>

using namespace std;

Jeu::Jeu()
{
}

Jeu::~Jeu()
{
}

void Jeu::jouer()
{
	sf::RenderWindow window(sf::VideoMode(665, 800), "What does the fox say ?");

	//Creation créature
	Creature Bestiole;


	//Textures
	sf::Texture backgroundDay;
	sf::Texture backgroundNight;
	sf::Texture texturePerso;
	sf::Texture cursor;
	sf::Texture portraitCrea;
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
	//Création des sprites
	sf::Sprite backgroundD(backgroundDay);
	sf::Sprite backgroundN(backgroundNight);
	sf::Sprite spriteSoleil(jour, daynight);
	sf::Sprite spriteLune(nuit, daynight);
	sf::Sprite spritePerso(texturePerso, rectSource);
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

	bool isDay = true;
	bool isDragging = false;

	//Coordonnées
	sf::Vector2i posSouris;
	spritePerso.setPosition(100, 380);
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
	spriteCursor.setTextureRect(rectCursor);

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
	//Creation nourriture
	Nourriture Repas;
	//Creation medicament
	Medicament Soin;

	sf::Clock clock;
	float elapsed=0;

	while (window.isOpen())
	{
		//Creation horloge interne

		sf::Event event;

		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			spriteCursor.setPosition((sf::Vector2f)sf::Mouse::getPosition(window));


			if (casesSelection[0].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				onMenu = true;
			}
			if (event.type == event.KeyReleased && event.key.code == sf::Keyboard::Escape)
			{
				onMenu = false;
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
			else
			{
				isDragging = false;
			}


			//Laver
			if (casesSelection[7].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
			{
				Bestiole.laver();
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

		if (elapsed >= 4000 && onMenu==false)
		{
			Bestiole.setFaim(Bestiole.getFaim() - 5);
			rectBarFaim.width = int(169 * Bestiole.getFaim() / Bestiole.getFaimMax());
			spriteHungryBar.setTextureRect(rectBarFaim);

			Bestiole.setEnergie(Bestiole.getEnergie() - 5);
			rectBarNrj.width = int(169 * Bestiole.getEnergie() / Bestiole.getEnergieMax());
			spriteEnergyBar.setTextureRect(rectBarNrj);

			elapsed = 0;
		}

		//Faire ses besoins
		if (Bestiole.getNbNourris() == 3)
		{
			Bestiole.faireCaca();
		}
		//Statut deprime
		else if (Bestiole.getNbCacas() >= 3)
		{
			Bestiole.setStatut(deprime);
		}
		//Gain niveau
		else if (Bestiole.getExpActuel() == Bestiole.getExpMax())
		{
			Bestiole.gagnerNiveau(Bestiole);
		}
		//Evolution
		else if (Bestiole.getNiveau() == 3)
		{
			Bestiole.evoluer(Bestiole, enfant);
		}
		//Statut extenue
		else if (Bestiole.getEnergie() <= 20)
		{
			Bestiole.setStatut(extenue);
		}
		//Statut deprime
		else if (Bestiole.getJoie() <= 20)
		{
			Bestiole.setStatut(deprime);
		}
		//Statut affame
		else if (Bestiole.getFaim() <= 20)
		{
			Bestiole.setStatut(affame);
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

		for (unsigned int i = 0; i < casesSelection.size(); i++)
		{
			window.draw(casesSelection[i]);
		}

		window.draw(nomCrea);
		//Crea
		if (Bestiole.enVie = true)
		{
			window.draw(spritePerso);
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

		if (onMenu == true)
		{
			window.draw(spriteMenuIG);
		}

		//Curseur
		window.draw(spriteCursor);
		window.display();
	}
}