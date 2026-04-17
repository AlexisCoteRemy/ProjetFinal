#include "game.h"

#include "mesConstantes.h"

#include <fstream>

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
	_currentInputPlayer = 1;

	_winText.setFont(_font);
	_winText.setCharacterSize(40);
	_winText.setPosition(WINDOW_WIDTH / 2.0f, 0);

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

	_player.setFont(_font);
	_player.setCharacterSize(40);
	_player.setFillColor(Color::White);
	_player.setOutlineThickness(2);
	_player.setPosition(325, 200);

	_prompt.setFont(_font);
	_prompt.setCharacterSize(40);
	_prompt.setFillColor(Color::Black);
	_prompt.setPosition(10, 200);

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
	if (_state == 4)
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Enter)
			{
				if (_currentInputPlayer == 1)
				{
					_player1Name = _playerName;
					_playerName = "";
					_currentInputPlayer = 2;
				}
				else
				{
					_player2Name = _playerName;
					_state = 1;
					_joueurActuel = 1;
					_winText.setString("Tour de " + _player1Name);
					FloatRect bounds = _winText.getLocalBounds();
					_winText.setOrigin(bounds.left + bounds.width / 2.0f, 0);
				}
			}
		}
		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode == 8)
			{
				if (!_playerName.isEmpty())
				{
					_playerName.erase(_playerName.getSize() - 1);
				}
			}
			else if (event.text.unicode < 128 && event.text.unicode >= 32)
			{
				_playerName += event.text.unicode;
			}

			_player.setString(_playerName);
		}
	}
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

							if (_player1Name.isEmpty() || _player2Name.isEmpty())
							{
								_state = 4;
							}
							else
							{
								_state = 1;
							}
							
							if (!_gameStarted)
							{
								_grid.initializeGrid();
								_gameOver = false;
								_joueurActuel = 1;
								_currentInputPlayer = 1;
								_winText.setString("Tour de " + _player1Name);
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
									_winText.setString("Victoire de " + _player1Name);
									FloatRect bounds = _winText.getLocalBounds();
									_winText.setOrigin(bounds.left + bounds.width / 2.0f, 0);
								}
								else if (_winner == 2)
								{
									_winText.setString("Victoire de " + _player2Name);
									FloatRect bounds = _winText.getLocalBounds();
									_winText.setOrigin(bounds.left + bounds.width / 2.0f, 0);
								}
								else
								{
									_winText.setString("Partie nulle :( !");
									FloatRect bounds = _winText.getLocalBounds();
									_winText.setOrigin(bounds.left + bounds.width / 2.0f, 0);
									_joueurActuel = 3;
								}
							}
							else
							{
								_joueurActuel = 3 - _joueurActuel;
								if (_joueurActuel == 1)
								{
									_winText.setString("Tour de " +  _player1Name);
									_winText.setOutlineColor(Color::Red);
									_winText.setOutlineThickness(2);
									FloatRect bounds = _winText.getLocalBounds();
									_winText.setOrigin(bounds.left + bounds.width / 2.0f, 0);
								}
								else
								{
									_winText.setString("Tour de " + _player2Name);
									_winText.setOutlineColor(Color::Yellow);
									_winText.setOutlineThickness(2);
									FloatRect bounds = _winText.getLocalBounds();
									_winText.setOrigin(bounds.left + bounds.width / 2.0f, 0);
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

			else
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
	else if (_state == 2 || _state == 3 || _state == 4)
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
	else if (_state == 3)
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
	else
	{
		_title.setPosition(180, 5);
		_title.setString("Entrez vos noms\n    d'utilisateurs");
		window.draw(_title);
		if (_currentInputPlayer == 1)
		{
			_prompt.setString("Nom du joueur 1:");
			_prompt.setFillColor(Color::White);
			_prompt.setOutlineThickness(2);
		}
		else
		{
			_prompt.setString("Nom du joueur 2:");
			_prompt.setFillColor(Color::White);
			_prompt.setOutlineThickness(2);
		}
		window.draw(_prompt);
		window.draw(_player);
		_backButton.draw(window);
	}
}
