#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "button.h"
#include "game.h"

using namespace sf;

int main() {

	RenderWindow window;
	button button(Color::Black, Color:: White, Color::Red, 200, 100, 2, 150, 150, 175, 175, 40, "Play");

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
		button.draw(window);
		window.display();
		
	}
	return 0;
}