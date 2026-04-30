#pragma once

#include "Button.h"
#include "State.h"
#include "SoundManager.h"
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
    
    SoundManager& _sounds;
 
public:
    Menu(SoundManager& sounds);

    void handleEvent(sf::Event& event, sf::RenderWindow& window, State& state, bool needName);
    void hover(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};