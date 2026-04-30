#include "FallingToken.h"

bool FallingToken::isFalling() const
{
	return _falling;
}

bool FallingToken::isStopped() const
{
	return _stopped;
}

int FallingToken::getCol() const
{
	return _col;
}

int FallingToken::getRow() const
{
	return _row;
}

int FallingToken::getPlayer() const
{
	return _player;
}

void FallingToken::start(int col, int row, int player)
{
	_col = col;
	_row = row;
	_player = player;

	_y = CENTER_Y - CELLSIZE;
	_targetY = CENTER_Y + row * CELLSIZE + 5;
	_speed = 600.f;

	_falling = true;
	_stopped = false;
}

void FallingToken::update(float deltaTime)
{
	if (!_falling)
	{
		return;
	}

	_y += _speed * deltaTime;

	if (_y >= _targetY)
	{
		_y = _targetY;
		_falling = false;
		_stopped = true;
	}
}

void FallingToken::draw(RenderWindow& window)
{
	if (!_falling && !_stopped) return;

	CircleShape token(CELLSIZE / 2 - 5);

	if (_player == 1)
	{
		token.setFillColor(Color::Red);
	}
	else
	{
		token.setFillColor(Color::Yellow);
	}

	float x = CENTER_X + _col * CELLSIZE + 5;

	token.setPosition(x, _y);

	window.draw(token);
}
