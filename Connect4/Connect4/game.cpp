#include "Game.h"
#include "mesFonctions.h"

using namespace sf;
using namespace std;

Game::Game() : _nameInput(_joueur), _jeu(_joueur)
{
    _state = MENU;
}

void Game::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == Event::Closed)
    {
        _previousState = _state;
        _state = QUIT_MENU;
    }

    bool needName = (_joueur.getPlayer1Name().isEmpty() || _joueur.getPlayer2Name().isEmpty());;

    if (_state == MENU)
    {
        _menu.handleEvent(event, window, _state, needName);
    }
    else if (_state == LEADERBOARD)
    {
        _classement.handleEvent(event, window, _state);
    }
    else if (_state == HOW_TO)
    {
        _commentJouer.handleEvent(event, window, _state);
    }
    else if (_state == NAME_INPUT)
    {
        _nameInput.handleEvent(event, window, _state);
    }
    else if (_state == GAME)
    {
        _jeu.handleEvent(event, window, _state);
    }
    else if (_state == QUIT_MENU)
    {
        _quit.handleEvent(event, window, _state, _previousState);
    }
    else
    {
        _saveLoad.handleEvent(event, window, _state, _wantSave, _wantLoad, _jeu);
    }
}

void Game::draw(sf::RenderWindow& window)
{
    if (_state == MENU)
    {
        _menu.draw(window);
    }
    else if (_state == LEADERBOARD)
    {
        _classement.draw(window);
    }
    else if (_state == HOW_TO)
    {
        _commentJouer.draw(window);
    }
    else if (_state == NAME_INPUT)
    {
        _nameInput.draw(window);
    }
    else if (_state == GAME)
    {
        _jeu.draw(window);
    }
    else if (_state == QUIT_MENU)
    {
        _quit.hover(window);
    }
    else
    {
        _saveLoad.draw(window, _state);
    }
}

void Game::hover(sf::RenderWindow& window)
{
    if (_state == MENU)
    {
        _menu.hover(window);
    }
    else if (_state == LEADERBOARD)
    {
        _classement.hover(window);
    }
    else if (_state == HOW_TO)
    {
        _commentJouer.hover(window);
    }
    else if (_state == NAME_INPUT)
    {
        _nameInput.hover(window);
    }
    else if (_state == GAME)
    {
        _jeu.hover(window);
    }
    else if (_state == QUIT_MENU)
    {
        _quit.draw(window);
    }
    else
    {
        _saveLoad.hover(window, _state);
    }
}

void Game::processActions()
{
    if (_wantSave)
    {
        _jeu.saveGame();
        _wantSave = false;
    }

    if (_wantLoad)
    {
        _jeu.loadGame();
        _wantLoad = false;
    }

    if (_state == GAME)
    {
        _jeu.update(_state);
    }
}
