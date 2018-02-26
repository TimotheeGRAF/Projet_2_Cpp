#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "GRAF Timothée");
	//Texture
	sf::Texture texturePerso;
	texturePerso.loadFromFile("alien.png");
	//Rectangle de sélection
	sf::IntRect rectSource(0, 0, 64, 64);
	//Création du sprite
	sf::Sprite spritePerso(texturePerso, rectSource);
	//Limitation du framerate
	window.setFramerateLimit(24);

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

			spritePerso.move(0, -4);
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

			spritePerso.move(0, 4);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
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

		window.clear();
		window.draw(spritePerso);
		window.display();

	}
	return 0;
}