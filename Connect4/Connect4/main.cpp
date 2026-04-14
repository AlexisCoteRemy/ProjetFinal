#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "button.h"
#include "game.h"

using namespace sf;
using namespace std;

int main() {

	int state = 0;

	vector<Button> buttons;

	Font font;

	font.loadFromFile("arial.ttf");

	buttons.push_back(Button(150, 150, 210, 150, "Play", font));
	buttons.push_back(Button(150, 210, 210, 210, "Leaderboard", font));
	buttons.push_back(Button(150, 270, 210, 270, "How to play", font));
	buttons.push_back(Button(150, 330, 210, 330, "Quit", font));

	Button backButton(150, 500, 210, 500, "Back", font);

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
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					Vector2i mousePos = Mouse::getPosition(window);

					if (state == 0)
					{
						for (int i = 0; i < buttons.size(); i++)
						{
							if (buttons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
							{
								if (i == 0)
								{
									//game.play()
									state = 1;
								}
								if (i == 1)
								{
									state = 2;
								}
								if (i == 2)
								{
									state = 3;
								}
								if (i == 3)
								{
									window.close();
								}
							}
						}
					}
					else if (state == 2)
					{
						if(backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
						{
							state = 0;
						}
					}
					else if (state == 3)
					{
						if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
						{
							state = 0;
						}
					}
				}
			}
		}

		window.clear(Color::Black);
		
		Vector2i mousePos = Mouse::getPosition(window);

		if (state == 0)
		{
			for (int i = 0; i < buttons.size(); i++)
			{
				if (buttons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
				{
					buttons[i].setFillColor(Color::Green);
				}
				else
				{
					buttons[i].setFillColor(Color::White);
				}

				buttons[i].draw(window);
			}
		}
		else if (state == 2)
		{
			//window.draw(leaderboard)
			if (backButton.getGlobalBounds().contains(mousePos.x,mousePos.y))
			{
				backButton.setFillColor(Color::Green);
			}
			else
			{
				backButton.setFillColor(Color::White);
			}

			backButton.draw(window);
		}
		else if (state == 3)
		{
			//window.draw(howtoplay)
			if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
			{
				backButton.setFillColor(Color::Green);
			}
			else
			{
				backButton.setFillColor(Color::White);
			}

			backButton.draw(window);
		}

		window.display();
		
	}
	return 0;
}