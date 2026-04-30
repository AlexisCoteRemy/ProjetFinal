#include "Jeu.h"
#include "mesFonctions.h"
#include <fstream>

using namespace sf;

Jeu::Jeu(Joueur& joueur, SoundManager& sounds) : _joueur(joueur), _sounds(sounds)
{
	_font.loadFromFile("ITCAvantGardePro-Md.ttf");

	_grid.initializeGrid();
	_gamerOver = false;
	_gameStarted = true;
	_blinkState = false;
	_waitingForLeaderboard = false;
	_winner = 0;
	_joueur.setCurrentInputPlayer(1);
	_joueur.setJoueurAcutel(1);

	_winText.setFont(_font);
	_winText.setCharacterSize(40);
	updateTurnText();
	_winText.setFillColor(Color::White);
	_winText.setOutlineColor(Color::Red);
	_winText.setOutlineThickness(2);

	FloatRect bounds = _winText.getLocalBounds();
	_winText.setOrigin(bounds.width / 2, bounds.height / 2);
	_winText.setPosition(WINDOW_WIDTH / 2, 20);

	_backButton = Button((WINDOW_WIDTH - BACK_BUTTON_WIDTH) / 2, (WINDOW_HEIGHT + 20 - (MAIN_BUTTON_HEIGHT * 2)), (WINDOW_WIDTH - BACK_BUTTON_WIDTH) / 2, (WINDOW_HEIGHT + 20 - (MAIN_BUTTON_HEIGHT * 2)), BACK_BUTTON_WIDTH + 10, 50, "Retour", _font);
}

void Jeu::handleEvent(sf::Event& event, sf::RenderWindow& window, State& state)
{
	if (_fallingToken.isFalling())
		return;

	if (event.type == Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == Mouse::Left)
		{
			Vector2i mousePos = Mouse::getPosition(window);

			if (!_gamerOver)
			{
				if (_backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
				{
					backButtonPressed(state);
				}

				int col = _grid.clicked(mousePos);

				if (col != -1)
				{
					_sounds.play("click");

					if (!_fallingToken.isFalling())
					{
						int row = -1;

						for (int i = ROWS - 1; i >= 0; i--)
						{
							if (_grid.getCell(i, col) == 0)
							{
								row = i;
								break;
							}
						}

						if (row != -1)
						{
							_fallingToken.start(col, row, _joueur.getJoueurActuel());
							_sounds.play("click");
						}
					}
				}
			}
		}
		
	}
	else if (event.type == Event::KeyPressed)
	{
		if (event.key.code == Keyboard::Escape)
			backButtonPressed(state);
	}
}

void Jeu::hover(sf::RenderWindow& window)
{
	if (_gamerOver)
	{
		return;
	}

	Vector2i mousePos = Mouse::getPosition(window);

	int col = _grid.clicked(mousePos);

	if (col != -1)
	{
		_grid.hoverColumn(col, _joueur.getJoueurActuel());
	}
	else
	{
		_grid.hoverColumn(-1, _joueur.getJoueurActuel());
	}

	bool isHovered = _backButton.getGlobalBounds().contains(mousePos.x, mousePos.y);

	if (isHovered)
	{
		_backButton.setFillColor(Color(255, 255, 0, 225));
		_backButton.setScale(1.05f, 1.05f);
		_backButton.setTextScale(1.05f, 1.05f);

		if (!_backButton.wasHovered())
		{
			_sounds.play("hover");
		}
	}
	else
	{
		_backButton.setFillColor(Color(255, 255, 255, 175));
		_backButton.setScale(1.05f, 1.05f);
		_backButton.setTextScale(1.f, 1.f);
	}

	_backButton.setWasHovered(isHovered);
}

void Jeu::draw(sf::RenderWindow& window)
{
	window.draw(_winText);
	_grid.draw(window);
	_fallingToken.draw(window);

	if (_gamerOver)
	{
		if (_blink.getElapsedTime().asMilliseconds() >= 300)
		{
			_blinkState = !_blinkState;
			_blink.restart();
		}

		if (_blinkState)
		{
			if (_joueur.getJoueurActuel() == 1)
			{
				_winText.setFillColor(Color::Red);
				_winText.setOutlineColor(Color::Yellow);
				_winText.setOutlineThickness(2);
			}
			else if (_joueur.getJoueurActuel() == 2)
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

	if (!_gamerOver)
	{
		_backButton.draw(window);
	}
}

void Jeu::reset()
{
	_grid.initializeGrid();
	_gamerOver = false;
	_gameStarted = true;
	_blinkState = false;
	_waitingForLeaderboard = false;
	_winner = 0;
	_joueur.setJoueurAcutel(1);
	_joueur.setPlayer1Name("");
	_joueur.setPlayer2Name("");
	_joueur.setPlayerName("");
	_joueur.setCurrentInputPlayer(1);
	updateTurnText();
}

void Jeu::saveGame()
{
	if (_gamerOver)
	{
		return;
	}

	std::ofstream fileOut("save.txt");

	fileOut << _joueur.getPlayer1Name().toAnsiString() << std::endl;
	fileOut << _joueur.getPlayer2Name().toAnsiString() << std::endl;
	fileOut << _joueur.getJoueurActuel() << std::endl;

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			fileOut << _grid.getCell(i,j) << " ";
		}
		fileOut << std::endl;
	}

	fileOut.close();
}

bool Jeu::loadGame()
{
	std::ifstream fileIn("save.txt");

	if (fileIn.peek() == EOF)
	{
		return false;
	}

	std::string name1, name2;
	int joueurActuel;

	fileIn >> name1;
	fileIn >> name2;
	fileIn >> joueurActuel;

	_joueur.setPlayer1Name(name1);
	_joueur.setPlayer2Name(name2);
	_joueur.setJoueurAcutel(joueurActuel);

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			int value;
			fileIn >> value;
			_grid.setCell(i, j, value);
		}
	}

	fileIn.close();

	return true;
}

void Jeu::update(State& state)
{
	if (_waitingForLeaderboard)
	{
		if (_endClock.getElapsedTime().asSeconds() >= 3)
		{
			state = LEADERBOARD;
			_waitingForLeaderboard = false;
		}
	}

	float dt = _clock.restart().asSeconds();

	_fallingToken.update(dt);

	if (_fallingToken.isStopped())
	{
		int col = _fallingToken.getCol();
		int player = _fallingToken.getPlayer();

		_grid.drop(col, player);

		_fallingToken = FallingToken();

		_winner = _grid.getWinner();

		if (_winner != 0 || _grid.isFull())
		{
			_sounds.play("victory");
			_gamerOver = true;
			_gameStarted = false;
			_waitingForLeaderboard = true;
			_endClock.restart();

			std::ofstream fileOut("save.txt", std::ios::trunc);
			fileOut.close();

			if (_winner == 1)
			{
				_winText.setString("Victoire de " + _joueur.getPlayer1Name());

				FloatRect bounds = _winText.getLocalBounds();
				_winText.setOrigin(bounds.width / 2, bounds.height / 2);
				_winText.setPosition(WINDOW_WIDTH / 2, 20);
				updateVictory("classement.txt", _joueur.getPlayer1Name());
			}
			else if (_winner == 2)
			{
				_winText.setString("Victoire de " + _joueur.getPlayer2Name());

				FloatRect bounds = _winText.getLocalBounds();
				_winText.setOrigin(bounds.width / 2, bounds.height / 2);
				_winText.setPosition(WINDOW_WIDTH / 2, 20);
				updateVictory("classement.txt", _joueur.getPlayer2Name());
			}
			else
			{
				_winText.setString("Partie nulle :( !");

				FloatRect bounds = _winText.getLocalBounds();
				_winText.setOrigin(bounds.width / 2, bounds.height / 2);
				_winText.setPosition(WINDOW_WIDTH / 2, 20);
				_joueur.setJoueurAcutel(3);
			}
		}
		else
		{
			_joueur.setJoueurAcutel(3 - _joueur.getJoueurActuel());
			updateTurnText();
		}
	}
}

void Jeu::updateTurnText()
{
	if (_gamerOver)
	{
		return;
	}

	if (_joueur.getJoueurActuel() == 1)
	{
		_winText.setString("Tour de " + _joueur.getPlayer1Name());
		_winText.setOutlineColor(Color::Red);
	}
	else
	{
		_winText.setString("Tour de " + _joueur.getPlayer2Name());
		_winText.setOutlineColor(Color::Yellow);
	}

	_winText.setOutlineThickness(2);

	FloatRect bounds = _winText.getLocalBounds();
	_winText.setOrigin(bounds.width / 2, bounds.height / 2);
	_winText.setPosition(WINDOW_WIDTH / 2, 20);
}
void Jeu::backButtonPressed(State& state)
{

	if (_gamerOver)
	{
		_sounds.play("back");
		reset();
		state = MENU;
	}
	else
	{
		state = SAVE_MENU;
		_sounds.play("back");
	}
}
