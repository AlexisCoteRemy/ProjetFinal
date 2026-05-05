#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "State.h"
#include "mesConstantes.h"
<<<<<<< HEAD
//cleaned
=======

>>>>>>> e439a21de4660e41943f2166912786e63d2aeb55
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

