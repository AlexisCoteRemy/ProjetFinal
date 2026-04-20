#include "Jeu.h"
#include "mesFonctions.h"

using namespace sf;

Jeu::Jeu(Joueur& joueur) : _joueur(joueur)
{
	_font.loadFromFile("arial.ttf");

	_grid.initializeGrid();
	_gamerOver = false;
	_gameStarted = true;
	_blinkState = false;
	_winner = 0;
	_joueur.setCurrentInputPlayer(1);
	_joueur.setJoueurAcutel(1);

	_winText.setFont(_font);
	_winText.setCharacterSize(60);
	_winText.setString("Tour de " + _joueur.getPlayer1Name());
	_winText.setFillColor(Color::White);
	_winText.setOutlineColor(Color::Red);
	_winText.setOutlineThickness(2);

	FloatRect bounds = _winText.getLocalBounds();
	_winText.setOrigin(bounds.width / 2, bounds.height / 2);
	_winText.setPosition(WINDOW_WIDTH / 2, 20);

	_backButton = Button((WINDOW_WIDTH - BACK_BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - 10 - (MAIN_BUTTON_HEIGHT * 2)), (WINDOW_WIDTH - BACK_BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - 10 - (MAIN_BUTTON_HEIGHT * 2)), BACK_BUTTON_WIDTH, 50, "Retour", _font);

	_hoverBuffer.loadFromFile("hoverSound.wav");
	_hoverSound.setBuffer(_hoverBuffer);
	_hoverSound.setVolume(10);

	_clickBuffer.loadFromFile("clickSound.wav");
	_clickSound.setBuffer(_clickBuffer);
	_clickSound.setVolume(10);

	_victoryBuffer.loadFromFile("victorySound.wav");
	_victorySound.setBuffer(_victoryBuffer);
	_victorySound.setVolume(15);
}

void Jeu::handleEvent(sf::Event& event, sf::RenderWindow& window, State& state)
{
	if (event.type == Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == Mouse::Left)
		{
			Vector2i mousePos = Mouse::getPosition(window);

			if (_backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
			{
				if (_gamerOver)
				{
					reset();
				}
				_clickSound.play();
				state = MENU;
			}

			if (!_gamerOver)
			{
				int col = _grid.clicked(mousePos);

				if (col != -1)
				{
					_clickSound.play();

					if (_grid.drop(col, _joueur.getJoueurActuel()))
					{
						_winner = _grid.getWinner();

						if (_winner != 0 || _grid.isFull())
						{
							_victorySound.play();
							_gamerOver = true;
							_gameStarted = false;

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

							if (_joueur.getJoueurActuel() == 1)
							{
								_winText.setString("Tour de " + _joueur.getPlayer1Name());
								_winText.setOutlineColor(Color::Red);
								_winText.setOutlineThickness(2);
								FloatRect bounds = _winText.getLocalBounds();
								_winText.setOrigin(bounds.width / 2, bounds.height / 2);
								_winText.setPosition(WINDOW_WIDTH / 2, 20);
							}
							else
							{
								_winText.setString("Tour de " + _joueur.getPlayer2Name());
								_winText.setOutlineColor(Color::Yellow);
								_winText.setOutlineThickness(2);
								FloatRect bounds = _winText.getLocalBounds();
								_winText.setOrigin(bounds.width / 2, bounds.height / 2);
								_winText.setPosition(WINDOW_WIDTH / 2, 20);
							}
						}
					}
				}
			}
		}
	}
}

void Jeu::hover(sf::RenderWindow& window)
{
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

void Jeu::draw(sf::RenderWindow& window)
{
	if (_gameStarted && _winText.getString() == "Tour de ")
	{
		_winText.setString("Tour de " + _joueur.getPlayer1Name());
		FloatRect bounds = _winText.getLocalBounds();
		_winText.setOrigin(bounds.width / 2, bounds.height / 2);
		_winText.setPosition(WINDOW_WIDTH / 2, 20);

	}
	window.draw(_winText);
	_grid.draw(window);

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

	_backButton.draw(window);
}

void Jeu::reset()
{
	_grid.initializeGrid();
	_gamerOver = false;
	_gameStarted = true;
	_blinkState = false;
	_winner = 0;
	_joueur.setJoueurAcutel(1);
	_winText.setString("Tour de " + _joueur.getPlayer1Name());
	_winText.setFillColor(Color::White);
	_winText.setOutlineColor(Color::Red);
	_winText.setOutlineThickness(2);
	FloatRect bounds = _winText.getLocalBounds();
	_winText.setOrigin(bounds.width / 2, bounds.height / 2);
	_winText.setPosition(WINDOW_WIDTH / 2, 20);
	_joueur.setPlayer1Name("");
	_joueur.setPlayer2Name("");
	_joueur.setPlayerName("");
	_joueur.setCurrentInputPlayer(1);
}