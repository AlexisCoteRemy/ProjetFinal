#include "grid.h"
#include <vector>

using namespace std;
using namespace sf;

void Grid::initializeGrid()
{
	int gridWidth = COLS * _cellSize;
	int gridHeight = ROWS * _cellSize;

	int windowWidth = 800;
	int windowHeight = 608;

	int x = (windowWidth - gridWidth) / 2;
	int y = (windowHeight - gridHeight) / 2;

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
		CircleShape bouton(_cellSize / 2 - 5);

		bouton.setPosition(x + i * _cellSize + 5, y - _cellSize);
		bouton.setFillColor(Color::White);

		_boutons.push_back(bouton);
	}
}

void Grid::draw(sf::RenderWindow& window)
{
	int gridWidth = COLS * _cellSize;
	int gridHeight = ROWS * _cellSize;

	int windowWidth = 800;
	int windowHeight = 608;

	int x = (windowWidth - gridWidth) / 2;
	int y = (windowHeight - gridHeight) / 2;

	for (int i = 0; i < _boutons.size(); i++)
	{
		window.draw(_boutons[i]);
	}

	RectangleShape board(Vector2f(COLS * _cellSize, ROWS * _cellSize));
	board.setPosition(x, y);
	board.setFillColor(Color::Blue);
	window.draw(board);

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			CircleShape hole(_cellSize / 2 - 5);
			hole.setPosition(x + j * _cellSize + 5, y + i * _cellSize + 5);
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
				CircleShape jeton(_cellSize / 2 - 10);
				jeton.setPosition(x + j * _cellSize + 10, y + i * _cellSize + 10);

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
