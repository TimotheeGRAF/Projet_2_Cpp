#include "Jeu.h"





Jeu::Jeu()
{
	sf::RenderWindow window(sf::VideoMode(665, 800), "Un Xénomorph d'amour");

	//Textures
	sf::Texture backgroundDay;
	sf::Texture texturePerso;
	sf::Texture cursor;
	sf::Texture emptyBar;
	sf::Texture cadreCrea;
	sf::Texture portraitCrea;
	sf::Texture fruit;
	sf::Texture viande;
	sf::Texture biscuit;
	sf::Texture caca;
	sf::Texture nameBox;
	backgroundDay.loadFromFile("background.png");
	texturePerso.loadFromFile("Adulte.png");
	cursor.loadFromFile("Cursor.png");
	emptyBar.loadFromFile("EmptyBar.png");
	cadreCrea.loadFromFile("cadreCrea.png");
	portraitCrea.loadFromFile("portraitCrea.png");
	nameBox.loadFromFile("NameBox.png");
	fruit.loadFromFile("Fruit.png");
	viande.loadFromFile("Viande.png");
	biscuit.loadFromFile("Biscuit.png");
	caca.loadFromFile("Poop.png");

	//Rectangles de sélection
	sf::IntRect rectSource(0, 0, 64, 64);
	sf::IntRect rectCursor(0, 0, 32, 38);
	sf::IntRect rectEmptyBar(0, 0, 180, 80);
	sf::IntRect nourriture(0, 0, 50, 50);
	sf::IntRect rectCadreCrea(0, 0, 128, 128);
	sf::IntRect rectPortraitCrea(0, 0, 100, 128);
	sf::IntRect rectNameBox(0, 0, 209, 54);

	//Création des sprites
	sf::Sprite background(backgroundDay);
	sf::Sprite spritePerso(texturePerso, rectSource);
	sf::Sprite spriteCursor(cursor, rectCursor);
	sf::Sprite spriteEmptyBar(emptyBar, rectEmptyBar);
	sf::Sprite spriteCadreCrea(cadreCrea, rectCadreCrea);
	sf::Sprite spritePortraitCrea(portraitCrea, rectPortraitCrea);
	sf::Sprite spriteFruit(fruit, nourriture);
	sf::Sprite spriteViande(viande, nourriture);
	sf::Sprite spriteBiscuit(biscuit, nourriture);
	sf::Sprite spriteNameBox(nameBox, rectNameBox);

	//Coordonnées
	sf::Vector2i posSouris;
	spritePerso.setPosition(300, 558);
	spriteEmptyBar.setPosition(0, 0);
	spriteFruit.setPosition(360, 705);
	spriteViande.setPosition(420, 705);
	spriteBiscuit.setPosition(480, 705);
	spriteCadreCrea.setPosition(0, 672);
	spritePortraitCrea.setPosition(10, 672);
	spriteNameBox.setPosition(128, 680);
	//Limitation du framerate
	//window.setFramerateLimit(60);
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
	nomCrea.setPosition(180, 680);
	

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
		sf::FloatRect boxBiscuit = spriteBiscuit.getGlobalBounds();
		sf::FloatRect boxFruit = spriteFruit.getGlobalBounds();
		sf::FloatRect boxViande = spriteViande.getGlobalBounds();

		//On bouge le sprite du biscuit via drag&drop avec la souris

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (boxBiscuit.intersects(boxSouris)))
			{

				posSouris = sf::Mouse::getPosition(window);
				spriteBiscuit.setPosition(posSouris.x, posSouris.y);
				if (boxBiscuit.intersects(boxFruit))
				{
					spriteFruit.setPosition(360, 705);
				}
				else if (boxBiscuit.intersects(boxViande))
				{
					spriteViande.setPosition(420, 705);
				}
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (boxFruit.intersects(boxSouris)))
			{

				posSouris = sf::Mouse::getPosition(window);
				spriteFruit.setPosition(posSouris.x, posSouris.y);
				if (boxFruit.intersects(boxViande))
				{
					spriteViande.setPosition(420, 705);
				}
				else if (boxFruit.intersects(boxBiscuit))
				{
					spriteBiscuit.setPosition(480, 705);
				}
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (boxViande.intersects(boxSouris)))
			{

				posSouris = sf::Mouse::getPosition(window);
				spriteViande.setPosition(posSouris.x, posSouris.y);
				if (boxViande.intersects(boxFruit))
				{
					spriteFruit.setPosition(360, 705);
				}
				else if (boxViande.intersects(boxBiscuit))
				{
					spriteBiscuit.setPosition(480, 705);
				}
			}
		

		window.clear();
		window.draw(background);
		//UI
		window.draw(spriteEmptyBar);
		window.draw(spriteNameBox);
		window.draw(nomCrea);
		window.draw(spritePortraitCrea);
		window.draw(spriteCadreCrea);
		//Crea
		window.draw(spritePerso);
		window.draw(spriteBiscuit);
		window.draw(spriteFruit);
		window.draw(spriteViande);
		//Curseur
		window.draw(spriteCursor);
		window.display();
	}
}


Jeu::~Jeu()
{
}
