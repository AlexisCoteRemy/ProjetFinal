#include "button.h"

Button::Button(int bX, int bY, int tX, int tY, std::string nom)
{
	_font.loadFromFile("arial.ttf");

	_button.setSize(Vector2f(200,50));
	_button.setFillColor(Color::White);
	_button.setOutlineColor(Color::Red);
	_button.setOutlineThickness(2);
	_button.setPosition(bX, bY);

	_texte.setCharacterSize(40);
	_texte.setString(nom);
	_texte.setFillColor(Color::Black);
	_texte.setPosition(tX, tY);
	_texte.setFont(_font);
}

void Button::draw(RenderWindow& window) const
{
	window.draw(_button);
	window.draw(_texte);
	
}

FloatRect Button::getGlobalBounds() const
{
	return _button.getGlobalBounds();
}
