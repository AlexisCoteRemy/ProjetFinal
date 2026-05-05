#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "button.h"
#include "SoundManager.h"
#include "MusicManager.h"
#include "mesConstantes.h"
#include "Localization.h"
#include <vector>
#include <string>

class Settings
{
public:
	Settings(SoundManager& sounds, MusicManager& music, Localization& loc);
	void handleEvent(sf::Event& event, sf::RenderWindow& window, State& state);
	void hover(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void updateTexts();

private:
	std::vector<Button> _buttons;
	Button _backButton;
	Button _languageButton;
	sf::Font _font;
	sf::Text _title;
	sf::RectangleShape _textBox;
	std::vector<Button> _volPlusButtons;
	std::vector<Button> _volMinusButtons;

	std::vector<sf::Text> _labels;

	SoundManager& _sounds;
	MusicManager& _music;

	Localization& _loc;
};