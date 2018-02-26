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
	backgroundDay.loadFromFile("backgroundDay.png");
	texturePerso.loadFromFile("alien.png");
	//Rectangle de sélection
	sf::IntRect rectSource(0, 0, 64, 64);
	//Création des sprites
	sf::Sprite background(backgroundDay);
	sf::Sprite spritePerso(texturePerso, rectSource);
	
	//Coordonnées
	spritePerso.setPosition(100, 400);
	//Limitation du framerate
	window.setFramerateLimit(24);
	window.setMouseCursorVisible(true);
	window.setMouseCursorGrabbed(false);
	//Creation horloge interne
	sf::Clock clock;

	

	while (window.isOpen())
	{
		//Touches de déplacement (à faire en switch-case)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			rectSource.top = 64*3;

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

			spritePerso.move(0, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			rectSource.top = 0;

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

			spritePerso.move(0, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)/* || spritePerso.getPosition().x + spritePerso.getLocalBounds().width >= window.getSize().x*/)
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
			//spritePerso.move(4, 0);
			if (spritePerso.getPosition().x == 0)
			{
				spritePerso.move(4, 0);
			}
			else
			{
				spritePerso.move(-4, 0);
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)/* || spritePerso.getPosition().x <= 0*/)
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
			if (spritePerso.getPosition().x == 0)
			{
				spritePerso.move(-4, 0);
			}
			else
			{
				spritePerso.move(4, 0);
			}
		}

		//Collisions bordure fenêtre


		window.clear();
		window.draw(background);
		window.draw(spritePerso);
		window.display();

	}
	
	return 0;

}