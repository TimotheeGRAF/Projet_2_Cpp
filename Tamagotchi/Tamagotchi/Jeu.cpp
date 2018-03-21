#include "Jeu.h"
#include <iostream>
#include <vector>


using namespace std;

Jeu::Jeu()
{
	sf::RenderWindow window(sf::VideoMode(665, 800), "Un Xénomorph d'amour");

	//Textures
	sf::Texture backgroundDay;
	sf::Texture backgroundNight;
	sf::Texture texturePerso;
	sf::Texture cursor;
	sf::Texture portraitCrea;
	sf::Texture alpha;
	sf::Texture jour;
	sf::Texture nuit;

	backgroundDay.loadFromFile("background1.png");
	backgroundNight.loadFromFile("background2.png");
	texturePerso.loadFromFile("Poupon.png");
	cursor.loadFromFile("Cursor.png");
	//portraitCrea.loadFromFile("portraitCrea.png");
	jour.loadFromFile("Soleil.png");
	nuit.loadFromFile("Lune.png");

	//Rectangles de sélection
	sf::IntRect rectSource(0, 0, 240, 275);
	sf::IntRect rectCursor(0, 0, 32, 38);
	sf::IntRect selectBox(0, 0, 50, 50);
	//sf::IntRect rectPortraitCrea(0, 0, 100, 128);
	sf::IntRect daynight(0, 0, 100, 100);
	//Création des sprites
	sf::Sprite backgroundD(backgroundDay);
	sf::Sprite backgroundN(backgroundNight);
	sf::Sprite spriteSoleil(jour, daynight);
	sf::Sprite spriteLune(nuit, daynight);
	sf::Sprite spritePerso(texturePerso, rectSource);
	sf::Sprite spriteCursor(cursor, rectCursor);
	//sf::Sprite spritePortraitCrea(portraitCrea, rectPortraitCrea);
	sf::Sprite spriteSelection(alpha, selectBox);
	spriteSelection.setColor(sf::Color::Transparent);

	//création vector de sprites de sélection
	vector<sf::Sprite> casesSelection;
	for (int i = 1; i <= 10; i++)
	{
		casesSelection.push_back(spriteSelection);
	}

	bool isDay = true;

	//Coordonnées
	sf::Vector2i posSouris;
	spritePerso.setPosition(100, 345);
	//spritePortraitCrea.setPosition(10, 674);
	spriteSoleil.setPosition(460, 10);
	spriteLune.setPosition(460, 10);
	casesSelection[0].setPosition(150, 710);
	casesSelection[1].setPosition(231, 685);
	casesSelection[2].setPosition(308, 685);
	casesSelection[3].setPosition(386, 685);
	casesSelection[4].setPosition(231, 745);
	casesSelection[5].setPosition(308, 745);
	casesSelection[6].setPosition(386, 745);
	casesSelection[7].setPosition(478, 713);
	casesSelection[8].setPosition(575, 684);
	casesSelection[9].setPosition(575, 741);
	//Bordures des Sprites
	sf::FloatRect boxPerso = spritePerso.getGlobalBounds();
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
	//Creation créature
	Creature Bestiole;
	Bestiole.setNom("Poupette");
	nomCrea.setString(Bestiole.getNom());
	nomCrea.setPosition(482, 410);
	//Creation nourriture
	Nourriture Repas;
	//Creation medicament
	Medicament Soin;

	//Creation horloge interne
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}


			// event.Type == event.MouseButtonReleased && event.MouseButton.Button == sf::Mouse::Left


			if (casesSelection[0].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				gameState::menu;
			}
			else if (casesSelection[1].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
			{
				Repas.donnerAManger(Repas.fruit);
			}
			else if (casesSelection[2].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
			{
				Repas.donnerAManger(Repas.viande);
			}
			else if (casesSelection[3].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
			{
				Repas.donnerAManger(Repas.biscuit);
			}
			else if (casesSelection[4].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
			{
				Bestiole.soigner(Soin.stimulant, Bestiole);
			}
			else if (casesSelection[5].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
			{
				Bestiole.soigner(Soin.hyperproteine, Bestiole);
			}
			else if (casesSelection[6].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
			{
				Bestiole.soigner(Soin.antidepresseur, Bestiole);
			}
			else if (casesSelection[7].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
			{
				Bestiole.laver();
			}
			else if (casesSelection[8].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
			{
				isDay = true;
			}
			else if (casesSelection[9].getGlobalBounds().intersects(spriteCursor.getGlobalBounds()) && (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
			{
				isDay = false;
			}
		}
		window.setKeyRepeatEnabled(false);

		spriteCursor.setPosition((sf::Vector2f)sf::Mouse::getPosition(window));


		/*sf::FloatRect boxBiscuit = spriteBiscuit.getGlobalBounds();
		sf::FloatRect boxFruit = spriteFruit.getGlobalBounds();
		sf::FloatRect boxViande = spriteViande.getGlobalBounds();*/

		//On bouge le sprite du biscuit via drag&drop avec la souris

			//if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (boxBiscuit.intersects(boxSouris)))
			//{


			//	spriteBiscuit.setPosition(posSouris.x, posSouris.y);
			//	if (boxBiscuit.intersects(boxFruit))
			//	{
			//		spriteFruit.setPosition(360, 705);
			//	}
			//	else if (boxBiscuit.intersects(boxViande))
			//	{
			//		spriteViande.setPosition(420, 705);
			//	}
			//}
			//else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (boxFruit.intersects(boxSouris)))
			//{	

			//	posSouris = sf::Mouse::getPosition(window);
			//	spriteFruit.setPosition(posSouris.x, posSouris.y);
			//	if (boxFruit.intersects(boxViande))
			//	{
			//		spriteViande.setPosition(420, 705);
			//	}
			//	else if (boxFruit.intersects(boxBiscuit))
			//	{
			//		spriteBiscuit.setPosition(480, 705);
			//	}
			//}
			//else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (boxViande.intersects(boxSouris)))
			//{	

			//	posSouris = sf::Mouse::getPosition(window);
			//	spriteViande.setPosition(posSouris.x, posSouris.y);
			//	if (boxViande.intersects(boxFruit))
			//	{
			//		spriteFruit.setPosition(360, 705);
			//	}
			//	else if (boxViande.intersects(boxBiscuit))
			//	{
			//		spriteBiscuit.setPosition(480, 705);
			//	}
			//}


		//Logique Creature

		if (Bestiole.getNbNourris() == 3)
		{
			Bestiole.faireCaca();
		}
		else if (Bestiole.getNbCacas() == 3)
		{
			Bestiole.setStatut(deprime);
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

		for (int i = 0; i < casesSelection.size(); i++)
		{
			window.draw(casesSelection[i]);
		}

		window.draw(nomCrea);
		//window.draw(spritePortraitCrea);
		//Crea
		window.draw(spritePerso);
		//Curseur
		window.draw(spriteCursor);
		window.display();
	}
}


Jeu::~Jeu()
{
}
