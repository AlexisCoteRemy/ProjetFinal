#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "button.h"
#include "State.h"
#include "Jeu.h"

class SaveLoad
{
public:
	SaveLoad();

	void handleEvent(sf::Event& event, sf::RenderWindow& window, State& state, bool& wantSave, bool& wantLoad, Jeu& jeu);
	void hover(sf::RenderWindow& window, State& state);
	void draw(sf::RenderWindow& window, State& state);

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
	sf::SoundBuffer _hoverBuffer;
	sf::SoundBuffer _clickBuffer;
	sf::SoundBuffer _backBuffer;
	sf::SoundBuffer _warningBuffer;

	sf::Sound _hoverSound;
	sf::Sound _clickSound;
	sf::Sound _backSound;
	sf::Sound _warningSound;
};