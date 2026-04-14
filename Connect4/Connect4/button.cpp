#include "button.h"

button::button(Color colorText, Color colorButton, Color colorOutline, int w, int h, int thickness, int bX, int bY, int tX, int tY, int charSize, std::string nom)
{
	_font.loadFromFile("arial.ttf");

	_button.setSize(Vector2f(w, h));
	_button.setFillColor(colorButton);
	_button.setOutlineColor(colorOutline);
	_button.setOutlineThickness(thickness);
	_button.setPosition(bX, bY);

	_texte.setCharacterSize(charSize);
	_texte.setString(nom);
	_texte.setFillColor(colorText);
	_texte.setPosition(tX, tY);
	_texte.setFont(_font);
}

void button::draw(RenderWindow& window) const
{
	window.draw(_button);
	window.draw(_texte);
	
}
