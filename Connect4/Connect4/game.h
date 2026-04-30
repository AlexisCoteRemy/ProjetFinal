#pragma once

#include "Menu.h"
#include "Classement.h"
#include "CommentJouer.h"
#include "NameInput.h"
#include "Joueur.h"
#include "Jeu.h"
#include "Button.h"
#include "Quit.h"
#include "mesConstantes.h"
#include "SaveLoad.h"
#include "State.h"
#include "SoundManager.h"
#include <SFML/Graphics.hpp>

class Game
{
private:
    Menu _menu;
    Classement _classement;
    CommentJouer _commentJouer;
    NameInput _nameInput;
    SaveLoad _saveLoad;
    Jeu _jeu;
    Quit _quit;
    Joueur _joueur;
    State _state;
    State _previousState;
    SoundManager _sounds;

    bool _wantSave;
    bool _wantLoad;

public:
    Game();

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void hover(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void processActions();
};