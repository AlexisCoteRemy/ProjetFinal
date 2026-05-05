#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"

//cleaned
int main() {
	sf::RenderWindow window(sf::VideoMode(800, 533), "Connect 4");
	window.setFramerateLimit(60);

	sf::Texture backgroudImage;
	backgroudImage.loadFromFile("c4.jpg");

	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroudImage);
	backgroundSprite.setColor(sf::Color(255, 255, 255, 75));

	Game game;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			game.handleEvent(event, window);
		}

		game.processActions();

		window.clear();
		window.draw(backgroundSprite);
		game.hover(window);
		game.draw(window);
		window.display();
	}
}