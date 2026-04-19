#pragma once

#include "Menu.h"
#include "Classement.h"
#include "CommentJouer.h"
#include "NameInput.h"
#include "Joueur.h"
#include "Jeu.h"
#include "Button.h"
#include "mesConstantes.h"
#include "State.h"
#include <SFML/Graphics.hpp>

class Game
{
private:
    Menu _menu;
    Classement _classement;
    CommentJouer _commentJouer;
    NameInput _nameInput;
    Jeu _jeu;
    Joueur _joueur;
    State _state;

public:
    Game();

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void hover(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};