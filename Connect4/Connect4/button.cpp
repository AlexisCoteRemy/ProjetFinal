#include "button.h"

Button::Button()
{
}

Button::Button(int x, int y, int r)
{
	_circle.setRadius(r);
	_circle.setPosition(x, y);
	_circle.setFillColor(Color::White);

	_isCircle = true;
}

Button::Button(int bX, int bY, int tX, int tY, int w, int h, std::string nom, Font& font)
{
	_button.setSize(Vector2f(w,h));
	_button.setFillColor(Color::White);
	_button.setOutlineColor(Color::Red);
	_button.setOutlineThickness(2);
	_button.setPosition(bX, bY);

	_texte.setCharacterSize(40);
	_texte.setString(nom);
	_texte.setFillColor(Color::Black);
	_texte.setPosition(tX, tY);
	_texte.setFont(font);

	_wasHovered = false;
	_wasClicked = false;
	_isCircle = false;
}

void Button::draw(RenderWindow& window) const
{
	if (_isCircle)
	{
		window.draw(_circle);
	}
	else
	{
		window.draw(_button);
		window.draw(_texte);
	}
}

void Button::setFillColor(Color color)
{
	if (_isCircle)
	{
		_circle.setFillColor(color);
	}
	else
	{
		_button.setFillColor(color);
	}
}

FloatRect Button::getGlobalBounds() const
{
	if (_isCircle)
	{
		return _circle.getGlobalBounds();
	}
	else
	{
		return _button.getGlobalBounds();
	}
}

bool Button::wasHovered() const
{
	return _wasHovered;
}

void Button::setWasHovered(bool state)
{
	_wasHovered = state;
}
