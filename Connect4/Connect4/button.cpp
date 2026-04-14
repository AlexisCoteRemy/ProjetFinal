#include "button.h"

Button::Button(int bX, int bY, int tX, int tY, std::string nom, Font& font)
{
	_button.setSize(Vector2f(350,50));
	_button.setFillColor(Color::White);
	_button.setOutlineColor(Color::Red);
	_button.setOutlineThickness(2);
	_button.setPosition(bX, bY);

	_texte.setCharacterSize(40);
	_texte.setString(nom);
	_texte.setFillColor(Color::Black);
	_texte.setPosition(tX, tY);
	_texte.setFont(font);
}

void Button::draw(RenderWindow& window) const
{
	window.draw(_button);
	window.draw(_texte);
}

void Button::setFillColor(Color color)
{
	_button.setFillColor(color);
}

FloatRect Button::getGlobalBounds() const
{
	return _button.getGlobalBounds();
}
