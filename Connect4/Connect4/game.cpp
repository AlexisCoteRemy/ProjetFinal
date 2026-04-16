#include "game.h"

#include "mesConstantes.h"

using namespace std;

Game::Game()
{
    _font.loadFromFile("arial.ttf");

	_title.setFont(_font);
	_title.setCharacterSize(60);
	_title.setFillColor(Color::White);
	_title.setOutlineColor(Color::Red);
	_title.setOutlineThickness(2);

    _buttons.push_back(Button(250, 150, 255, 150, 300, 50, "Jouer", _font));
    _buttons.push_back(Button(250, 210, 255, 210, 300, 50, "Classement", _font));
    _buttons.push_back(Button(250, 270, 255, 270, 300, 50, "Comment jouer", _font));
    _buttons.push_back(Button(250, 330, 255, 330, 300, 50, "Quitter", _font));

	_backButton = Button((WINDOW_WIDTH - 125) / 2, 500, (WINDOW_WIDTH - 125) / 2, 500, 125, 50, "Retour", _font);

	_state = 0;
	_joueurActuel = 1;
	_winner = 0;
	_gameOver = false;
	_gameStarted = false;
	_blinkState = false;

	_winText.setFont(_font);
	_winText.setCharacterSize(40);
	_winText.setPosition(250, 0);

	_howTo.setFont(_font);
	_howTo.setCharacterSize(20);
	_howTo.setPosition(Vector2f((WINDOW_WIDTH - 590) / 2, (WINDOW_HEIGHT - 375) / 2));
	_howTo.setFillColor(Color::Black);
	_howTo.setOutlineColor(Color::White);
	_howTo.setOutlineThickness(0.5);
	

	_textBox.setSize(Vector2f(600, 375));
	_textBox.setFillColor(Color(255, 255, 255, 175));
	_textBox.setPosition(Vector2f((WINDOW_WIDTH - 600) / 2, (WINDOW_HEIGHT - 375) / 2));
	_textBox.setOutlineColor(Color::Red);
	_textBox.setOutlineThickness(2);

	_backgroundImage.loadFromFile("c4.jpg");
	_backgroundSprite.setTexture(_backgroundImage);
	_backgroundSprite.setColor(Color(255,255,255,75));

	_hoverBuffer.loadFromFile("hoverSound.wav");
	_hoverSound.setBuffer(_hoverBuffer);
	_hoverSound.setVolume(10);

	_clickBuffer.loadFromFile("clickSound.wav");
	_clickSound.setBuffer(_clickBuffer);
	_clickSound.setVolume(10);

	_victoryBuffer.loadFromFile("victorySound.wav");
	_victorySound.setBuffer(_victoryBuffer);
	_victorySound.setVolume(10);

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

			// ==== MENU ====

			if (_state == 0)
			{
				for (int i = 0; i < _buttons.size(); i++)
				{
					bool isClicked = _buttons[i].getGlobalBounds().contains(mousePos.x, mousePos.y);

					if (isClicked)
					{
						if (i == 0)
						{
							_clickSound.play();

							_state = 1;
							
							if (!_gameStarted)
							{
								_grid.initializeGrid();
								_gameOver = false;
								_joueurActuel = 1;
								_winText.setString("Tour du joueur " + to_string(_joueurActuel));
								_gameStarted = true;
								_blinkState = false;
								_winText.setFillColor(Color::White);
								_winText.setOutlineColor(Color::Red);
								_winText.setOutlineThickness(2);
							}
						}
						if (i == 1)
						{
							_clickSound.play();
							_state = 2;
						}
						if (i == 2)
						{
							_clickSound.play();
							_state = 3;
						}
						if (i == 3)
						{
							_clickSound.play();
							window.close();
						}
					}
				}
			}

			// ==== JEU ====

			else if (_state == 1)
			{
				if (_backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
				{
					_clickSound.play();
					_state = 0;
				}
				else if (!_gameOver)
				{
					int col = _grid.clicked(mousePos);

					if (col != -1)
					{
						_clickSound.play();

						if (_grid.drop(col, _joueurActuel))
						{
							_winner = _grid.getWinner();

							if (_winner != 0 || _grid.isFull())
							{
								_victorySound.play();
								_gameOver = true;
								_gameStarted = false;

								if (_winner == 1)
								{
									_winText.setString("Victoire joueur 1!");
								}
								else if (_winner == 2)
								{
									_winText.setString("Victoire joueur 2!");
								}
								else
								{
									_winText.setString("Partie nulle :( !");
									_joueurActuel = 3;
								}
							}
							else
							{
								_joueurActuel = 3 - _joueurActuel;
								if (_joueurActuel == 1)
								{
									_winText.setString("Tour du joueur " + to_string(_joueurActuel));
									_winText.setOutlineColor(Color::Red);
									_winText.setOutlineThickness(2);
								}
								else
								{
									_winText.setString("Tour du joueur " + to_string(_joueurActuel));
									_winText.setOutlineColor(Color::Yellow);
									_winText.setOutlineThickness(2);
								}
								
							}
						}
					}
				}
			}

			// ==== LEADERBOARD ====

			else if (_state == 2)
			{
				if (_backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
				{
					_clickSound.play();
					_state = 0;
				}
			}

			// ==== HOW TO PLAY ====

			else if (_state == 3)
			{

				if (_backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
				{
					_clickSound.play();
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
			bool isHovered = _buttons[i].getGlobalBounds().contains(mousePos.x, mousePos.y);

			if (isHovered)
			{
				_buttons[i].setFillColor(Color(255, 255, 0, 225));

				if (!_buttons[i].wasHovered())
				{
					_hoverSound.play();
				}
			}
			else
			{
				_buttons[i].setFillColor(Color(255, 255, 255, 175));
			}

			_buttons[i].setWasHovered(isHovered);
		}
	}
	else if (_state == 1)
	{
		int col = _grid.clicked(mousePos);

		if (col != -1)
		{
			_grid.hoverColumn(col, _joueurActuel);
		}
		else
		{
			_grid.hoverColumn(-1, _joueurActuel);
		}

		bool isHovered = _backButton.getGlobalBounds().contains(mousePos.x, mousePos.y);

		if (isHovered)
		{
			_backButton.setFillColor(Color(255, 255, 0, 225));

			if (!_backButton.wasHovered())
			{
				_hoverSound.play();
			}
		}
		else
		{
			_backButton.setFillColor(Color(255, 255, 255, 175));
		}

		_backButton.setWasHovered(isHovered);
	}
	else if (_state == 2 || _state == 3)
	{
		bool isHovered = _backButton.getGlobalBounds().contains(mousePos.x, mousePos.y);

		if (isHovered)
		{
			_backButton.setFillColor(Color(255, 255, 0, 225));

			if (!_backButton.wasHovered())
			{
				_hoverSound.play();
			}
		}
		else
		{
			_backButton.setFillColor(Color(255, 255, 255, 175));
		}

		_backButton.setWasHovered(isHovered);
	}
}

void Game::draw(sf::RenderWindow& window)
{
	window.draw(_backgroundSprite);

	if (_state == 0)
	{
		

		_title.setString("Connect4");
		_title.setPosition(265, 50);
		window.draw(_title);

		for (int i = 0; i < _buttons.size(); i++)
		{
			_buttons[i].draw(window);
		}
	}
	else if (_state == 1)
	{
		window.draw(_winText);
		_grid.draw(window);

		if (_gameOver)
		{
			if (_blink.getElapsedTime().asMilliseconds() >= 300)
			{
				_blinkState = !_blinkState;
				_blink.restart();
			}

			if (_blinkState)
			{
				if (_joueurActuel == 1)
				{
					_winText.setFillColor(Color::Red);
					_winText.setOutlineColor(Color::Yellow);
					_winText.setOutlineThickness(2);
				}
				else if (_joueurActuel == 2)
				{
					_winText.setFillColor(Color::Yellow);
					_winText.setOutlineColor(Color::Red);
					_winText.setOutlineThickness(2);
				}
				else
				{
					_winText.setFillColor(Color::Black);
					_winText.setOutlineColor(Color::Green);
					_winText.setOutlineThickness(2);
				}
				
			}
			else
			{
				_winText.setFillColor(Color::White);
			}
		}

		_backButton.draw(window);
	}
	else if (_state == 2)
	{
		//window.draw(leaderboard)
		_title.setPosition(250, 5);
		_title.setString("Classement");
		window.draw(_title);
		window.draw(_textBox);
		_backButton.draw(window);
	}
	else
	{
		//window.draw(howtoplay)
		window.draw(_textBox);
		_title.setPosition(200, 5);
		_title.setString("Comment jouer");
		window.draw(_title);
		_howTo.setString("\nAppuyez sur les cercles blancs en haut de la grille pour faire \ntomber un jeton.\n\nLes jetons rouges sont pour le premier joueur, et les jetons\njaunes sont pour le deuxieme joueur.\n\nLe premier joueur à aligner quatre jetons dans n'importe\nquelle direction gagne!\n\nBonne chance, et rappelez-vous, c'est un jeu!");
		window.draw(_howTo);
		_backButton.draw(window);
	}
}
