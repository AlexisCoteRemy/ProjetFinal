#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "State.h"
#include "mesConstantes.h"

class Classement
{
private:
    sf::Font _font;

    sf::Text _title;
    sf::Text _users;
    sf::Text _victories;
    sf::RectangleShape _textBox;

    sf::Texture _arrowTexture;
    sf::Sprite _upArrow;
    sf::Sprite _downArrow;

    Button _backButton;
    Button _effacer;

    sf::SoundBuffer _hoverBuffer;
    sf::SoundBuffer _clickBuffer;
    sf::SoundBuffer _backBuffer;

    sf::Sound _hoverSound;
    sf::Sound _clickSound;
    sf::Sound _backSound;

    std::vector<std::string> _noms;
    std::vector<int> _victoires;
    std::vector<sf::Text> _texts;
    std::vector<sf::RectangleShape> _rows;

    int _offset;
    int _maxVisible;

public:
    Classement();

    void handleEvent(sf::Event& event, sf::RenderWindow& window, State& state);
    void hover(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void loadScores(std::string nameFile);
};