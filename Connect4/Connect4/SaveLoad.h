#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SoundManager.h"
#include "Localization.h"
#include "button.h"
#include "State.h"
#include "Jeu.h"

//cleaned
class SaveLoad
{
public:
	SaveLoad(SoundManager& sounds, Localization& loc);

	void handleEvent(sf::Event& event, sf::RenderWindow& window, State& state, bool& wantSave, bool& wantLoad, Jeu& jeu);
	void hover(sf::RenderWindow& window, State& state);
	void draw(sf::RenderWindow& window, State& state);
	void setFillColor(Color color);
	void updateTexts();

private:
	std::vector<Button> _saveButtons;
	std::vector<Button> _loadButtons;
	sf::Font _font;
	sf::Text _title;
	sf::Text _warning;
	sf::Text _saved;
	bool _showWarning;
	bool _showSaved;
	sf::Clock _warningClock;
	sf::Clock _savedClock;
	
	SoundManager& _sounds;

	Localization& _loc;
};