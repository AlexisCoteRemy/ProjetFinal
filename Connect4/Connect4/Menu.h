#pragma once

#include "Button.h"
#include "State.h"
#include "mesConstantes.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

class Menu
{
private:
    std::vector<Button> _buttons;
    sf::Font _font;
    sf::Text _title;

    sf::SoundBuffer _hoverBuffer;
    sf::SoundBuffer _clickBuffer;

    sf::Sound _hoverSound;
    sf::Sound _clickSound;

public:
    Menu();

    void handleEvent(sf::Event& event, sf::RenderWindow& window, State& state, bool needName);
    void hover(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};