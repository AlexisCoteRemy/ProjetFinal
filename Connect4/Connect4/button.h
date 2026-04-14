#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Button
{
public:
	Button(int bX, int bY, int tX, int tY, std::string nom);
	~Button() = default;

	void draw(RenderWindow& window) const;
	FloatRect getGlobalBounds() const;

private:
	RectangleShape _button;
	Text _texte;
	Font _font;
};

