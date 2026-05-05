#pragma once

#include "Button.h"
#include "State.h"
#include "SoundManager.h"
#include "mesConstantes.h"
#include "Localization.h"
#include "SaveLoad.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
//cleaned

class Menu
{
private:
    std::vector<Button> _buttons;
    sf::Font _font;
    sf::Text _title;
    
    SoundManager& _sounds;
    Localization& _loc;
 
public:
    Menu(SoundManager& sounds, Localization& loc);

    void handleEvent(sf::Event& event, sf::RenderWindow& window, State& state, bool needName);
    void hover(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void updateTexts();
};