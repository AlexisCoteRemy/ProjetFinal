#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "button.h"
#include "State.h"

class SaveLoad
{
public:
	SaveLoad();

	void handleEvent(sf::Event& event, sf::RenderWindow& window, State& state);
	void hover(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

private:
	std::vector<Button> _buttons;
	sf::Font _font;
	sf::Text _title;
	sf::SoundBuffer _hoverBuffer;
	sf::SoundBuffer _clickBuffer;

	sf::Sound _hoverSound;
	sf::Sound _clickSound;
};