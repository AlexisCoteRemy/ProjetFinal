#pragma once

#include <SFML/Graphics.hpp>
#include "button.h"
<<<<<<< HEAD
//cleaned
=======
#include "mesConstantes.h"

>>>>>>> e439a21de4660e41943f2166912786e63d2aeb55

class Grid
{
public:

	void initializeGrid();
	void draw(sf::RenderWindow& window);

	bool drop(int col, int joueur);

	int clicked(sf::Vector2i mousePos);

	void hoverColumn(int col, int joueurActuel);

	int getWinner() const;

	bool isFull() const;

	int getCell(int i, int j) const;

	void setCell(int i, int j, int value);

private:
	int _grille[6][7];
	std::vector<Button> _boutons;
};
