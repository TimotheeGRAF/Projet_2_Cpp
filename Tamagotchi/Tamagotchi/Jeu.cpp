#include "Jeu.h"



Jeu::Jeu()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Un Xénomorph d'amour");

	//Textures
	sf::Texture backgroundDay;
//	sf::Texture textureUI;
	sf::Texture texturePerso;
	sf::Texture cursor;
	backgroundDay.loadFromFile("backgroundDay.png");
//	textureUI.loadFromFile("UI.png");
	texturePerso.loadFromFile("alien.png");
	cursor.loadFromFile("Cursor.png");
	//Rectangles de sélection
	sf::IntRect rectSource(0, 0, 64, 64);
	sf::IntRect rectCursor(0, 0, 32, 38);
	//Création des sprites
//	sf::Sprite GUI(textureUI);
	sf::Sprite background(backgroundDay);
	sf::Sprite spritePerso(texturePerso, rectSource);
	sf::Sprite spriteCursor(cursor, rectCursor);
	//Coordonnées
	sf::Vector2i posSouris;
	spritePerso.setPosition(100, 400);
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
	nomCrea.setCharacterSize(40);
	nomCrea.setFillColor(sf::Color::White);
	//Creation créature
	Creature Bestiole;
	Bestiole.setNom();
	nomCrea.setString(Bestiole.getNom());
	nomCrea.setPosition(150, 525);



	//Creation horloge interne
	sf::Clock clock;

	while (window.isOpen())
	{



		spriteCursor.setPosition((sf::Vector2f)sf::Mouse::getPosition(window));

		//Touches de déplacement (à faire en switch-case)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && spritePerso.getPosition().x + spritePerso.getLocalBounds().width <= window.getSize().x)
		{
			//On change de sprite chaque 0.07 secondes tant que la touche est pressée
			if (clock.getElapsedTime().asSeconds() > 0.07f)	
			{
				rectSource.top = 64 * 2;
				switch (rectSource.left)
				{
				case 0:
					rectSource.left = 64;
					spritePerso.setTextureRect(rectSource);
					clock.restart();
					break;
				case 64:
					rectSource.left = 64 * 2;
					spritePerso.setTextureRect(rectSource);
					clock.restart();
					break;
				case 64 * 2:
					rectSource.left = 64 * 3;
					spritePerso.setTextureRect(rectSource);
					clock.restart();
					break;
				case 64 * 3:
					rectSource.left = 0;
					spritePerso.setTextureRect(rectSource);
					clock.restart();
					break;
				}
				spritePerso.move(5, 0);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && spritePerso.getPosition().x >= 0)
		{
			//On change de sprite chaque 0.07 secondes tant que la touche est pressée
			if (clock.getElapsedTime().asSeconds() > 0.07f)
			{
				rectSource.top = 64;
				switch (rectSource.left)
				{
				case 0:
					rectSource.left = 64;
					spritePerso.setTextureRect(rectSource);
					clock.restart();
					break;
				case 64:
					rectSource.left = 64 * 2;
					spritePerso.setTextureRect(rectSource);
					clock.restart();
					break;
				case 64 * 2:
					rectSource.left = 64 * 3;
					spritePerso.setTextureRect(rectSource);
					clock.restart();
					break;
				case 64 * 3:
					rectSource.left = 0;
					spritePerso.setTextureRect(rectSource);
					clock.restart();
					break;
				}
				spritePerso.move(-5, 0);
			}
		}

		//Bordures des Sprites
		sf::FloatRect boxPerso = spritePerso.getGlobalBounds();
		sf::FloatRect boxSouris = spriteCursor.getGlobalBounds();

		//On bouge le sprite du perso via drag&drop avec la souris
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (boxPerso.intersects(boxSouris)))
		{
			posSouris = sf::Mouse::getPosition(window);
			spritePerso.setPosition(posSouris.x, posSouris.y);
			rectCursor.left = 32;
		}
		else
		{
			rectCursor.left = 0;
		}


		window.clear();
		window.draw(background);
		window.draw(spritePerso);
//		window.draw(GUI);
		window.draw(nomCrea);
		window.draw(spriteCursor);
		


		window.display();

	}
}


Jeu::~Jeu()
{
}
