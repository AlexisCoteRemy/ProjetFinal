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
	RenderWindow window(VideoMode(800, 608), "Connect4");
	window.setFramerateLimit(60);

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