#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include "Jeu.h"
#include "Creature.h"
#include "Nourriture.h"
#include "Options.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "GRAF Timothée");
	//Textures
	sf::Texture backgroundDay;
	sf::Texture texturePerso;
	sf::Texture cursor;
	backgroundDay.loadFromFile("backgroundDay.png");
	texturePerso.loadFromFile("alien.png");
	cursor.loadFromFile("Cursor.png");
	//Rectangle de sélection pour personnage
	sf::IntRect rectSource(0, 0, 64, 64);
	sf::IntRect rectCursor(0,0,32,38);
	//Création des sprites
	sf::Sprite background(backgroundDay);
	sf::Sprite spritePerso(texturePerso, rectSource);
	sf::Sprite spriteCursor(cursor, rectCursor);

	
	//Coordonnées
	spritePerso.setPosition(100, 400);
	//Limitation du framerate
	window.setFramerateLimit(18);
	window.setMouseCursorVisible(false);
	
	//Creation horloge interne
	sf::Clock clock;

	

	while (window.isOpen())
	{
		//Touches de déplacement (à faire en switch-case)
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		//{
		//	rectSource.top = 64*3;

		//	switch (rectSource.left)
		//	{
		//	case 0:
		//		rectSource.left = 64;
		//		spritePerso.setTextureRect(rectSource);
		//		break;
		//	case 64:
		//		rectSource.left = 64 * 2;
		//		spritePerso.setTextureRect(rectSource);
		//		break;
		//	case 64 * 2:
		//		rectSource.left = 64 * 3;
		//		spritePerso.setTextureRect(rectSource);
		//		break;
		//	case 64 * 3:
		//		rectSource.left = 0;
		//		spritePerso.setTextureRect(rectSource);
		//		break;
		//	}

		//	spritePerso.move(0, 0);
		//}
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		//{
		//	rectSource.top = 0;


		//	spritePerso.move(0, 0);
		//}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && spritePerso.getPosition().x + spritePerso.getLocalBounds().width <= window.getSize().x)
		{
			rectSource.top = 64*2;
			switch (rectSource.left)
			{
			case 0:
				rectSource.left = 64;
				spritePerso.setTextureRect(rectSource);
				break;
			case 64:
				rectSource.left = 64 * 2;
				spritePerso.setTextureRect(rectSource);
				break;
			case 64 * 2:
				rectSource.left = 64 * 3;
				spritePerso.setTextureRect(rectSource);
				break;
			case 64 * 3:
				rectSource.left = 0;
				spritePerso.setTextureRect(rectSource);
				break;
			}
			spritePerso.move(4, 0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && spritePerso.getPosition().x >= 0)
		{
			rectSource.top = 64;
			switch (rectSource.left)
			{
			case 0:
				rectSource.left = 64;
				spritePerso.setTextureRect(rectSource);
				break;
			case 64:
				rectSource.left = 64 * 2;
				spritePerso.setTextureRect(rectSource);
				break;
			case 64 * 2:
				rectSource.left = 64 * 3;
				spritePerso.setTextureRect(rectSource);
				break;
			case 64 * 3:
				rectSource.left = 0;
				spritePerso.setTextureRect(rectSource);
				break;
			}
			spritePerso.move(-4, 0);
		}

		//On change le curseur quand on clique
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			rectCursor.left = 32;
			spriteCursor.setTextureRect(rectCursor);
		}
		else
		{
			rectCursor.left = 0;
			spriteCursor.setTextureRect(rectCursor);
		}



		window.clear();
		//On dessine un curseur de souris perso à la position du curseur.
		spriteCursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

		window.draw(background);
		window.draw(spritePerso);
		window.draw(spriteCursor);

		window.display();

	}
	
	return 0;

}