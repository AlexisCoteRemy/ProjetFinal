#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "State.h"
#include "Joueur.h"
#include "mesConstantes.h"

class NameInput
{
public:
    NameInput(Joueur& joueur);

    void handleEvent(sf::Event& event, sf::RenderWindow& window, State& state);
    void hover(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    sf::Font _font;

    sf::Text _title;
    sf::RectangleShape _textBox;
    sf::Text _texte;

    Button _backButton;

    Joueur& _joueur;

    sf::SoundBuffer _hoverBuffer;
    sf::SoundBuffer _clickBuffer;

    sf::Sound _hoverSound;
    sf::Sound _clickSound;
};