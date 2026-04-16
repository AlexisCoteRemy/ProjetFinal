#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>

#include "button.h"
#include "game.h"
#include "grid.h"

using namespace sf;
using namespace std;

int main() {
	RenderWindow window(VideoMode(800, 588), "Connect4");
	window.setFramerateLimit(60);

	SoundBuffer mainMusicBuffer;
	mainMusicBuffer.loadFromFile("mainMusic.wav");

	Sound mainMusic;
	mainMusic.setBuffer(mainMusicBuffer);
	mainMusic.setVolume(10);
	mainMusic.setLoop(true);
	mainMusic.play();

	Game game;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			game.handleEvent(event, window);
		}

		window.clear(Color::Black);
		game.hover(window);
		game.draw(window);
		window.display();
	}
	return 0;
}