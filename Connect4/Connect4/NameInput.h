#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "SoundManager.h"
#include "State.h"
#include "Joueur.h"
#include "mesConstantes.h"
#include "Localization.h"
//cleaned

class NameInput
{
public:
    NameInput(Joueur& joueur, SoundManager& sounds, Localization& loc);

    void handleEvent(sf::Event& event, sf::RenderWindow& window, State& state);
    void hover(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void updateTexts();

private:
    sf::Font _font;

    sf::Text _title;
    sf::RectangleShape _textBox;
    sf::Text _texte;

    Button _backButton;

    Joueur& _joueur;

    SoundManager& _sounds;

    Localization& _loc;
};