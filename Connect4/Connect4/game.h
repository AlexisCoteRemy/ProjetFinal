#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
    bool _gameStarted;
    bool _blinkState;

    Font _font;

    std::vector<Button> _buttons;
    Button _backButton;

    Text _winText;
    Text _gameTitle;
    Text _howTitle;
    Text _howTo;

    Clock _blink;

    Texture _backgroundImage;

    Sprite _backgroundSprite;

    SoundBuffer _hoverBuffer;
    SoundBuffer _clickBuffer;
    SoundBuffer _victoryBuffer;

    Sound _hoverSound;
    Sound _clickSound;
    Sound _victorySound;

    RectangleShape _textBox;


};