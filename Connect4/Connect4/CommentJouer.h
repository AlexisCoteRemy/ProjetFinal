#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SoundManager.h"
#include "Button.h"
#include "State.h"
#include "mesConstantes.h"

class CommentJouer
{
private:
    sf::Font _font;

    sf::Text _title;
    sf::RectangleShape _textBox;
    sf::Text _texte;

    Button _backButton;

    SoundManager& _sounds;

public:
    CommentJouer(SoundManager& sounds);

    void handleEvent(sf::Event& event, sf::RenderWindow& window, State& state);
    void hover(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};