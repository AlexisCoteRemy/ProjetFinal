#include "game.h"

Game::Game()
{
    _font.loadFromFile("arial.ttf");

    _buttons.push_back(Button(250, 150, 250, 150, "Play", _font));
    _buttons.push_back(Button(250, 210, 250, 210, "Leaderboard", _font));
    _buttons.push_back(Button(250, 270, 250, 270, "How to play", _font));
    _buttons.push_back(Button(250, 330, 250, 330, "Quit", _font));

	_backButton = Button(10, 500, 10, 500, "Back", _font);

	_state = 0;
	_joueurActuel = 1;
	_winner = 0;
	_gameOver = false;

    _grid.initializeGrid();
}

void Game::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
	if (event.type == Event::Closed)
		window.close();
	if (event.type == Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == Mouse::Left)
		{
			Vector2i mousePos = Mouse::getPosition(window);

			if (_state == 0)
			{
				for (int i = 0; i < _buttons.size(); i++)
				{
					if (_buttons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
					{
						if (i == 0)
						{
							_state = 1;
							_grid.initializeGrid();
							_gameOver = false;
							_joueurActuel = 1;
						}
						if (i == 1)
						{
							_state = 2;
						}
						if (i == 2)
						{
							_state = 3;
						}
						if (i == 3)
						{
							window.close();
						}
					}
				}
			}
			else if (_state == 1)
			{
				if (_backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
				{
					_state = 0;
				}
				else if (!_gameOver)
				{
					int col = _grid.clicked(mousePos);

					if (col != -1)
					{
						if (_grid.drop(col, _joueurActuel))
						{
							_winner = _grid.getWinner();

							if (_winner != 0)
							{
								_gameOver = true;
							}
							else
							{
								_joueurActuel = 3 - _joueurActuel;
							}
						}
					}
				}
			}
			else if (_state == 2)
			{
				if (_backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
				{
					_state = 0;
				}
			}
			else if (_state == 3)
			{
				if (_backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
				{
					_state = 0;
				}
			}
		}
	}
}

void Game::hover(sf::RenderWindow& window)
{
	Vector2i mousePos = Mouse::getPosition(window);

	if (_state == 0)
	{
		for (int i = 0; i < _buttons.size(); i++)
		{
			if (_buttons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
			{
				_buttons[i].setFillColor(Color::Green);
			}
			else
			{
				_buttons[i].setFillColor(Color::White);
			}
		}
	}
	else if (_state == 1)
	{
		if (_gameOver)
		{
			if (_winner == 1)
			{
				// Insérer le texte de victoire joueur 1
			}
			else
			{
				// Insérer le texte de victoire du joueur 2
			}
		}

		if (_backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
		{
			_backButton.setFillColor(Color::Green);
		}
		else
		{
			_backButton.setFillColor(Color::White);
		}
	}
	else if (_state == 2)
	{
		//window.draw(leaderboard)
		if (_backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
		{
			_backButton.setFillColor(Color::Green);
		}
		else
		{
			_backButton.setFillColor(Color::White);
		}
	}
	else if (_state == 3)
	{
		//window.draw(howtoplay)
		if (_backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
		{
			_backButton.setFillColor(Color::Green);
		}
		else
		{
			_backButton.setFillColor(Color::White);
		}
	}
}

void Game::draw(sf::RenderWindow& window)
{
	if (_state == 0)
	{
		for (int i = 0; i < _buttons.size(); i++)
		{
			_buttons[i].draw(window);
		}
	}
	else if (_state == 1)
	{
		_grid.draw(window);

		if (_gameOver)
		{
			if (_winner == 1)
			{
				// Dessiner le texte de victoire joueur 1
			}
			else
			{
				// Dessiner le texte de victoire du joueur 2
			}
		}

		_backButton.draw(window);
	}
	else if (_state == 2)
	{
		//window.draw(leaderboard)
		_backButton.draw(window);
	}
	else
	{
		//window.draw(howtoplay)
		_backButton.draw(window);
	}
}
