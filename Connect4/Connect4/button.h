#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Button
{
public:
	Button();
	Button(int bX, int bY, int tX, int tY, int w, int h, std::string nom, Font& font);
	~Button() = default;

	void draw(RenderWindow& window) const;
	void setFillColor(Color color);
	FloatRect getGlobalBounds() const;
	bool wasHovered() const;
	void setWasHovered(bool state);

private:
	RectangleShape _button;
	Text _texte;
	bool _wasHovered;
	bool _wasClicked;
};

