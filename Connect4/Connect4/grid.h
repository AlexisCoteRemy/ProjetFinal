#pragma once

#include <SFML/Graphics.hpp>
#include "button.h"
#include "mesConstantes.h"


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
