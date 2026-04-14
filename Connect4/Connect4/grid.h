#pragma once

#include <SFML/Graphics.hpp>


class Grid
{
public:

	void initializeGrid();
	void draw(sf::RenderWindow& window);

	bool drop(int col, int joueur);

	int clicked(sf::Vector2i mousePos);

	void hoverColumn(int col, int joueurActuel);

	int getWinner() const;

private:
	static const int ROWS = 6;
	static const int COLS = 7;
	int _cellSize = 60;
	int _grille[6][7];
	std::vector<sf::CircleShape> _boutons;
};
