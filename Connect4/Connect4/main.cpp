#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "game.h"

using namespace sf;

int main() {

	RenderWindow window;

	window.create(VideoMode(800, 608), "Connect4");
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear(Color::Black);
		window.display();
	}

	return 0;
}