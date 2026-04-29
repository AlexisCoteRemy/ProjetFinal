#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "button.h"
#include "mesConstantes.h"
#include <vector>
#include <string>

class Quit
{
public:
	Quit();
	void handleEvent(sf::Event& event, sf::RenderWindow& window, State& state, State& previousState);
	void hover(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

private:
    std::vector<Button> _buttons;
    sf::Font _font;
    sf::Text _title;

    sf::SoundBuffer _hoverBuffer;
    sf::SoundBuffer _clickBuffer;
    sf::SoundBuffer _backBuffer;

    sf::Sound _hoverSound;
    sf::Sound _clickSound;
    sf::Sound _backSound;
};