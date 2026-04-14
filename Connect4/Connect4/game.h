#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "grid.h"
#include "button.h"

class Game
{
public:
    Game();

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void hover(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    Grid _grid;

    int _state;
    int _joueurActuel;
    int _winner;
    bool _gameOver;

    sf::Font _font;

    std::vector<Button> _buttons;
    Button _backButton;

    sf::Text _winText;
};