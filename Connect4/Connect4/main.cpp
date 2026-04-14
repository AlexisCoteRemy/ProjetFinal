#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "button.h"
#include "game.h"

using namespace sf;

int main() {

	Button playButton(150, 150, 175, 175, "Play");

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
		playButton.draw(window);
		window.display();
		
	}
	return 0;
}