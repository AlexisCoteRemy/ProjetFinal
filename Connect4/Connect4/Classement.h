#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "State.h"
#include "SoundManager.h"
#include "mesConstantes.h"
#include "Localization.h"

//cleaned
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

    SoundManager& _sounds;

    Localization& _loc;

    std::vector<std::string> _noms;
    std::vector<int> _victoires;
    std::vector<sf::Text> _texts;
    std::vector<sf::RectangleShape> _rows;

    int _offset;
    int _maxVisible;

public:
    Classement(SoundManager& sounds, Localization& loc);

    void handleEvent(sf::Event& event, sf::RenderWindow& window, State& state);
    void hover(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void loadScores(std::string nameFile);
    void updateTexts();
};