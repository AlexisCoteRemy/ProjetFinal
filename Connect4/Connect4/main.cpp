#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 588), "Ma fenêtre");
	window.setFramerateLimit(60);

	sf::Texture backgroudImage;
	backgroudImage.loadFromFile("c4.jpg");

	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroudImage);
	backgroundSprite.setColor(sf::Color(255, 255, 255, 75));

	sf::SoundBuffer mainBuffer;
	mainBuffer.loadFromFile("mainMusic.wav");

	sf::Sound mainMusic;
	mainMusic.setBuffer(mainBuffer);
	mainMusic.setLoop(true);
	mainMusic.setVolume(10);
	mainMusic.play();

	Game game;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			game.handleEvent(event, window);
		}

		window.clear();
		window.draw(backgroundSprite);
		game.hover(window);
		game.draw(window);
		window.display();
	}
}