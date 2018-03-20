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
	portraitCrea.loadFromFile("portraitCrea.png");
	jour.loadFromFile("Soleil.png");
	nuit.loadFromFile("Lune.png");
	


	//Rectangles de sélection
	sf::IntRect rectSource(0, 0, 250, 295);
	sf::IntRect rectCursor(0, 0, 32, 38);
	sf::IntRect selectBox(0, 0, 50, 50);
	sf::IntRect rectPortraitCrea(0, 0, 100, 128);
	sf::IntRect daynight(0, 0, 100, 100);
	//Création des sprites
	sf::Sprite backgroundD(backgroundDay);
	sf::Sprite backgroundN(backgroundNight);
	sf::Sprite spriteSoleil(jour, daynight);
	sf::Sprite spriteLune(nuit, daynight);
	sf::Sprite spritePerso(texturePerso, rectSource);
	sf::Sprite spriteCursor(cursor, rectCursor);
	sf::Sprite spritePortraitCrea(portraitCrea, rectPortraitCrea);
	sf::Sprite spriteSelection(alpha, selectBox);

	//création vector de sprites de sélection
	vector<sf::Sprite> casesSelection;
	for (int i = 1; i <= 10; i++)
	{
		casesSelection.push_back(spriteSelection);
	}

	spriteSelection.setColor(sf::Color::Transparent);

	bool isDay = true;

	//Coordonnées
	sf::Vector2i posSouris;
	spritePerso.setPosition(124, 330);
	spritePortraitCrea.setPosition(10, 674);
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
	Bestiole.setNom();
	nomCrea.setString(Bestiole.getNom());
	nomCrea.setPosition(482, 410);
	//Creation nourriture
	Nourriture Repas;

	//Creation horloge interne
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
		}

		spriteCursor.setPosition((sf::Vector2f)sf::Mouse::getPosition(window));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		{
			isDay = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		{
			isDay = false;
		}

		//Touches de déplacement (à faire en switch-case)
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && spritePerso.getPosition().x + spritePerso.getLocalBounds().width <= window.getSize().x)
		//{
		//	//On change de sprite chaque 0.07 secondes tant que la touche est pressée
		//	if (clock.getElapsedTime().asSeconds() > 0.07f)	
		//	{
		//		rectSource.top = 64 * 2;
		//		switch (rectSource.left)
		//		{
		//		case 0:
		//			rectSource.left = 64;
		//			spritePerso.setTextureRect(rectSource);
		//			clock.restart();
		//			break;
		//		case 64:
		//			rectSource.left = 64 * 2;
		//			spritePerso.setTextureRect(rectSource);
		//			clock.restart();
		//			break;
		//		case 64 * 2:
		//			rectSource.left = 64 * 3;
		//			spritePerso.setTextureRect(rectSource);
		//			clock.restart();
		//			break;
		//		case 64 * 3:
		//			rectSource.left = 0;
		//			spritePerso.setTextureRect(rectSource);
		//			clock.restart();
		//			break;
		//		}
		//		spritePerso.move(5, 0);
		//	}
		//}
		//
		//
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && spritePerso.getPosition().x >= 0)
		//{
		//	//On change de sprite chaque 0.07 secondes tant que la touche est pressée
		//	if (clock.getElapsedTime().asSeconds() > 0.07f)
		//	{
		//		rectSource.top = 64;
		//		switch (rectSource.left)
		//		{
		//		case 0:
		//			rectSource.left = 64;
		//			spritePerso.setTextureRect(rectSource);
		//			clock.restart();
		//			break;
		//		case 64:
		//			rectSource.left = 64 * 2;
		//			spritePerso.setTextureRect(rectSource);
		//			clock.restart();
		//			break;
		//		case 64 * 2:
		//			rectSource.left = 64 * 3;
		//			spritePerso.setTextureRect(rectSource);
		//			clock.restart();
		//			break;
		//		case 64 * 3:
		//			rectSource.left = 0;
		//			spritePerso.setTextureRect(rectSource);
		//			clock.restart();
		//			break;
		//		}
		//		spritePerso.move(-5, 0);
		//	}
		//}


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
		for (int i = 1; i >= 10; i++)
		{
			window.draw(casesSelection[i]);
		}

		window.draw(nomCrea);
		window.draw(spritePortraitCrea);
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
