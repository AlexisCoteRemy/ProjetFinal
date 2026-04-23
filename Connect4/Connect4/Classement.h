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

    Button _backButton;
    Button _effacer;

    sf::SoundBuffer _hoverBuffer;
    sf::SoundBuffer _clickBuffer;

    sf::Sound _hoverSound;
    sf::Sound _clickSound;

    std::map<string, int> _scores;
    std::vector<sf::Text> _texts;

    int _offset;
    int _maxVisible;

public:
    Classement();

    void handleEvent(sf::Event& event, sf::RenderWindow& window, State& state);
    void hover(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void loadScores(std::string nameFile);
};