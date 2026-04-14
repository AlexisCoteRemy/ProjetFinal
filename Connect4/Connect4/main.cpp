#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "game.h"

<<<<<<< HEAD
int main() 
{
=======
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

>>>>>>> f7277f3677b70495cfb64fba7a02c266e67ae0d9
	return 0;
}