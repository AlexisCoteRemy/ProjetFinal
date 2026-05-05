#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "button.h"
#include "SoundManager.h"
#include "mesConstantes.h"
#include "Localization.h"
#include <vector>
#include <string>

class Quit
{
public:
	Quit(SoundManager& sounds, Localization& loc);
	void handleEvent(sf::Event& event, sf::RenderWindow& window, State& state, State& previousState);
	void hover(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void updateTexts();

private:
    std::vector<Button> _buttons;
    sf::Font _font;
    sf::Text _title;

	SoundManager& _sounds;

	Localization& _loc;
};