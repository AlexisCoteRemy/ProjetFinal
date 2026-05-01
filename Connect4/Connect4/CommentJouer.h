#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SoundManager.h"
#include "Button.h"
#include "State.h"
#include "mesConstantes.h"
#include "Localization.h"

class CommentJouer
{
private:
    sf::Font _font;

    sf::Text _title;
    sf::RectangleShape _textBox;
    sf::Text _texte;

    Button _backButton;

    SoundManager& _sounds;
    Localization& _loc;

public:
    CommentJouer(SoundManager& sounds, Localization& lol);

    void handleEvent(sf::Event& event, sf::RenderWindow& window, State& state);
    void hover(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void updateTexts();
};