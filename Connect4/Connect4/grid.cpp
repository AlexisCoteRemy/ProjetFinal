#include "grid.h"
#include "mesConstantes.h"
#include <vector>

using namespace std;
using namespace sf;

void Grid::initializeGrid()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			_grille[i][j] = 0;
		}
	}

	_boutons.clear();

	for (int i = 0; i < 7; i++)
	{
		Button bouton(CENTER_X + i * CELLSIZE + 5, CENTER_Y - CELLSIZE, CELLSIZE / 2 - 5);

		_boutons.push_back(bouton);
	}
}

void Grid::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < _boutons.size(); i++)
	{
		_boutons[i].draw(window);
	}

	RectangleShape board(Vector2f(GRID_WIDTH, GRID_HEIGHT));
	board.setPosition(CENTER_X, CENTER_Y);
	board.setFillColor(Color::Blue);
	window.draw(board);

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			CircleShape hole(CELLSIZE / 2 - 5);
			hole.setPosition(CENTER_X + j * CELLSIZE + 5, CENTER_Y + i * CELLSIZE + 5);
			hole.setFillColor(Color::Black);

			window.draw(hole);
		}
	}

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (_grille[i][j] != 0)
			{
				CircleShape jeton(CELLSIZE / 2 - 10);
				jeton.setPosition(CENTER_X + j * CELLSIZE + 10, CENTER_Y + i * CELLSIZE + 10);

				if (_grille[i][j] == 1)
					jeton.setFillColor(Color::Red);
				else
					jeton.setFillColor(Color::Yellow);

				window.draw(jeton);
			}
		}
	}
}

bool Grid::drop(int col, int joueur)
{
	for (int i = 5; i >= 0; i--)
	{
		if (_grille[i][col] == 0)
		{
			_grille[i][col] = joueur;
			return true;
		}
	}
	return false;
}

int Grid::clicked(sf::Vector2i mousePos)
{
	for (int i = 0; i < _boutons.size(); i++)
	{
		if (_boutons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
		{
			return i;
		}
	}

	return -1;
}

void Grid::hoverColumn(int col, int joueurActuel)
{
	for (int i = 0; i < _boutons.size(); i++)
	{
		if (i == col)
		{
			if (joueurActuel == 1)
			{
				_boutons[i].setFillColor(sf::Color::Red);
			}
			else
			{
				_boutons[i].setFillColor(sf::Color::Yellow);
			}
			
		}
		else
		{
			_boutons[i].setFillColor(sf::Color::White);
		}
	}
}

int Grid::getWinner() const
{
	// Horizontalement

	for (int i = 0; i < 6; i++) 
	{
		for (int j = 0; j < 4; j++)
		{
			if (_grille[i][j] != 0 && _grille[i][j] == _grille[i][j + 1] && _grille[i][j] == _grille[i][j + 2] && _grille[i][j] == _grille[i][j + 3])
			{
				return _grille[i][j];
			}
		}
	}

	// Verticalement

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (_grille[i][j] != 0 && _grille[i][j] == _grille[i + 1][j] && _grille[i][j] == _grille[i + 2][j] && _grille[i][j] == _grille[i + 3][j])
			{
				return _grille[i][j];
			}
		}
	}

	// Diagonale bas droite

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (_grille[i][j] != 0 && _grille[i][j] == _grille[i + 1][j + 1] && _grille[i][j] == _grille[i + 2][j + 2] && _grille[i][j] == _grille[i + 3][j + 3])
			{
				return _grille[i][j];
			}
		}
	}

	// Diagonale haut droite

	for (int i = 3; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (_grille[i][j] != 0 && _grille[i][j] == _grille[i - 1][j + 1] && _grille[i][j] == _grille[i - 2][j + 2] && _grille[i][j] == _grille[i - 3][j + 3])
			{
				return _grille[i][j];
			}
		}
	}

	return 0;
}

bool Grid::isFull() const
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (_grille[i][j] == 0)
			{
				return false;
			}
		}
	}
	return true;
}
