#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class button
{
public:
	button(Color colorText, Color colorButton, Color colorOutline, int w, int h, int thickness, int bX, int bY, int tX, int tY, int charSize, std::string nom);
	~button() = default;
	void draw(RenderWindow& window) const;

private:
	RectangleShape _button;
	Text _texte;
	Font _font;
};

