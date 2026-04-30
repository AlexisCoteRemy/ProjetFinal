#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "button.h"
#include "SoundManager.h"
#include "mesConstantes.h"
#include <vector>
#include <string>

class Settings
{
public:
	Settings(SoundManager& sounds);
	void handleEvent(sf::Event& event, sf::RenderWindow& window, State& state);
	void hover(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

private:
	std::vector<Button> _buttons;
	Button _backButton;
	sf::Font _font;
	sf::Text _title;

	SoundManager& _sounds;
};