#include "Game.h"
#include "mesFonctions.h"

using namespace sf;
using namespace std;

Game::Game() : _menu(_sounds, _loc),_nameInput(_joueur, _sounds, _loc),_jeu(_joueur, _sounds, _loc), _classement(_sounds, _loc), _commentJouer(_sounds, _loc), _saveLoad(_sounds, _loc), _quit(_sounds, _loc), _settings(_sounds, _music, _loc)
{
    _sounds.load("hover", "hoverSound.wav");
    _sounds.load("click", "clickSound.wav");
    _sounds.load("back", "backSound.wav");
    _sounds.load("save", "saveSound.wav");
    _sounds.load("victory", "victorySound.wav");
    _sounds.load("warning", "warningSound.wav");
    _sounds.load("keyboardType", "keyboardType.wav");
    _sounds.load("backspaceType", "backspaceType.wav");
    _sounds.setVolume(20);

    _music.load("mainMusic.wav");
    _music.play();
    _music.setVolume(2);

    _state = MENU;
    _previousState = MENU;
    _nextState = MENU;
    _wantLoad = false;
    _wantSave = false;
    _fadeRect.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    _fadeRect.setFillColor(Color(0, 0, 0, 0));
}

void Game::startTransition(State nextState)
{
    _isTransitioning = true;
    _fadingOut = true;
    _nextState = nextState;
}

void Game::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
    State oldState = _state;

    if (event.type == Event::Closed)
    {
        _sounds.play("click");
        _previousState = _state;
        startTransition(QUIT_MENU);
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
    else if (_state == SETTINGS)
    {
        _settings.handleEvent(event, window, _state);
    }
    else
    {
        _saveLoad.handleEvent(event, window, _state, _wantSave, _wantLoad, _jeu);
    }

    if (_state != oldState && oldState != QUIT_MENU)
    {
        _previousState = oldState;
    }

    if (_state == GAME && _previousState != GAME)
    {
        _jeu.updateTurnText();
    }

    if (_state != oldState)
    {
        startTransition(_state);
        _state = oldState;
    
        if (_state == NAME_INPUT)
        {
            _joueur.setPlayer1Name("");
            _joueur.setPlayer2Name("");
            _joueur.setPlayerName("");
            _joueur.setCurrentInputPlayer(1);
        }

        if (_state == GAME && oldState != NAME_INPUT)
        {
            _jeu.reset();
        }
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
        _quit.draw(window);
    }
    else if (_state == SETTINGS)
    {
        _settings.draw(window);
    }
    else
    {
        _saveLoad.draw(window, _state);
    }

    window.draw(_fadeRect);
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
        _quit.hover(window);
    }
    else if (_state == SETTINGS)
    {
        _settings.hover(window);
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

    _settings.updateTexts();
    _menu.updateTexts();
    _nameInput.updateTexts();
    _saveLoad.updateTexts();
    _jeu.updateTexts();
    _classement.updateTexts();
    _commentJouer.updateTexts();
    _quit.updateTexts();

    float dt = _clock.restart().asSeconds();

    if (_isTransitioning)
    {
        if (_fadingOut)
        {
            _alpha += _fadeSpeed * dt;

            if (_alpha >= 255)
            {
                _alpha = 255;
                _state = _nextState;
                _fadingOut = false;
            }
        }
        else
        {
            _alpha -= _fadeSpeed * dt;

            if (_alpha <= 0)
            {
                _alpha = 0;
                _isTransitioning = false;
            }
        }

        _fadeRect.setFillColor(sf::Color(0, 0, 0, _alpha));
    }
}
