#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "State.h"
#include "mesConstantes.h"

//cleaned



class FallingToken
{
private:
	bool _falling;
	bool _stopped;

	int _col;
	int _row;
	int _player;

	float _y;
	float _targetY;
	float _speed;

public:
	bool isFalling() const;
	bool isStopped() const;

	int getCol() const;
	int getRow() const;
	int getPlayer() const;

	void start(int col, int row, int player);
	void update(float deltaTime);
	void draw(RenderWindow& window);
};

