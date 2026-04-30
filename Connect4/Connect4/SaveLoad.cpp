#include "SaveLoad.h"
#include "Classement.h"
#include "mesConstantes.h"
#include "mesFonctions.h"
#include <fstream>

using namespace std;

SaveLoad::SaveLoad(SoundManager& sounds) : _sounds(sounds)
{
    _font.loadFromFile("ITCAvantGardePro-Md.ttf");

    _title.setFont(_font);
    _title.setCharacterSize(80);
    _title.setFillColor(Color::White);
    _title.setOutlineColor(Color::Red);
    _title.setOutlineThickness(2);
    _title.setString("Faites votre choix");

    FloatRect bounds = _title.getLocalBounds();
    _title.setOrigin(bounds.width / 2, bounds.height / 2);
    _title.setPosition(WINDOW_WIDTH / 2, 50);

    vector<string> labelsSave = { "Continuer", "Sauvegarder", "Menu" };
    vector<string> labelsLoad = { "Nouvelle", "Charger", "Menu" };

    for (int i = 0; i < labelsSave.size(); i++)
    {
        _saveButtons.push_back(Button(MAIN_BX, START_Y_MAIN_BUTTON + SPACING * i, MAIN_BX + 5, START_Y_MAIN_BUTTON + SPACING * i, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, labelsSave[i], _font));
    }

    for (int i = 0; i < labelsLoad.size(); i++)
    {
        _loadButtons.push_back(Button(MAIN_BX, START_Y_MAIN_BUTTON + SPACING * i, MAIN_BX + 5, START_Y_MAIN_BUTTON + SPACING * i, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, labelsLoad[i], _font));
    }

    _warning.setFont(_font);
    _warning.setString("Aucune partie sauvegardée");
    _warning.setCharacterSize(30);
    _warning.setFillColor(Color::Red);

    FloatRect bounds2 = _warning.getLocalBounds();
    _warning.setOrigin(bounds2.width / 2, bounds2.height / 2);
    _warning.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100);

    _saved.setFont(_font);
    _saved.setString("Partie sauvegardée");
    _saved.setCharacterSize(30);
    _saved.setFillColor(Color::Green);

    FloatRect bounds3 = _saved.getLocalBounds();
    _saved.setOrigin(bounds3.width / 2, bounds3.height / 2);
    _saved.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100);

    _showWarning = false;
    _showSaved = false;
}

void SaveLoad::handleEvent(sf::Event& event, sf::RenderWindow& window, State& state, bool& wantSave, bool& wantLoad, Jeu& jeu)
{
    if (event.type == Event::KeyPressed)
    {
        if (event.key.code == Keyboard::Escape)
        {
            _sounds.play("back");
            state = State::MENU;
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        Vector2i mousePos = sf::Mouse::getPosition(window);

        if (state == SAVE_MENU)
        {

            for (int i = 0; i < _saveButtons.size(); i++)
            {
                if (_saveButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    if (i == 0)
                    {
                        _sounds.play("click");
                        state = GAME;
                    }
                    else if (i == 1)
                    {
                        jeu.saveGame();
                        _sounds.play("save");
                        _showSaved = true;
                        _savedClock.restart();
                    }
                    else if (i == 2)
                    {
                        _sounds.play("back");
                        state = MENU;
                    }
                }
            }
        } 
        else
        {
            for (int i = 0; i < _loadButtons.size(); i++)
            {
                if (_loadButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    if (i == 0)
                    {
                        std::ofstream fileOut("save.txt", std::ios::trunc);
                        fileOut.close();
                        _sounds.play("click");
                        jeu.reset();
                        state = NAME_INPUT;
                    }
                    else if (i == 1)
                    {
                        bool hasGame = jeu.loadGame();
                        _sounds.play("click");

                        if (hasGame)
                        {
                            _showWarning = false;
                            state = GAME;
                        }
                        else
                        {
                            _sounds.play("warning");
                            _showWarning = true;
                            _warningClock.restart();
                        }
                    }
                    else if (i == 2)
                    {
                        _sounds.play("click");
                        state = MENU;
                    }
                }
            }
        }
    }
}

void SaveLoad::hover(sf::RenderWindow& window, State& state)
{
    Vector2i mousePos = sf::Mouse::getPosition(window);

    if (state == SAVE_MENU)
    {
        for (int i = 0; i < _saveButtons.size(); i++)
        {
            bool isHovered = _saveButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y);

            if (isHovered)
            {
                _saveButtons[i].setFillColor(Color(255, 255, 0, 225));
                _saveButtons[i].setScale(1.05f, 1.05f);
                _saveButtons[i].setTextScale(1.05f, 1.05f);

                if (!_saveButtons[i].wasHovered())
                {
                    _sounds.play("hover");
                }
            }
            else
            {
                _saveButtons[i].setFillColor(Color(255, 255, 255, 175));
                _saveButtons[i].setScale(1.f, 1.f);
                _saveButtons[i].setTextScale(1.f, 1.f);
            }

            _saveButtons[i].setWasHovered(isHovered);
        }
    }
    else
    {
        for (int i = 0; i < _loadButtons.size(); i++)
        {
            bool isHovered = _loadButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y);

            if (isHovered)
            {
                _loadButtons[i].setFillColor(Color(255, 255, 0, 225));
                _loadButtons[i].setScale(1.05f, 1.05f);
                _loadButtons[i].setTextScale(1.05f, 1.05f);

                if (!_loadButtons[i].wasHovered())
                {
                    _sounds.play("hover");
                }
            }
            else
            {
                _loadButtons[i].setFillColor(Color(255, 255, 255, 175));
                _loadButtons[i].setScale(1.f, 1.f);
                _loadButtons[i].setTextScale(1.f, 1.f);
            }

            _loadButtons[i].setWasHovered(isHovered);
        }
    }
}

void SaveLoad::draw(sf::RenderWindow& window,State& state)
{
    window.draw(_title);

    if (_showWarning)
    {
        if (_warningClock.getElapsedTime().asSeconds() < 2)
        {
            window.draw(_warning);
        }
        else
        {
            _showWarning = false;
        }
    }

    if (_showSaved)
    {
        if (_savedClock.getElapsedTime().asSeconds() < 2)
        {
            window.draw(_saved);
        }
        else
        {
            _showSaved = false;
        }
    }

    if (state == SAVE_MENU)
    {
        for (int i = 0; i < _saveButtons.size(); i++)
        {
            _saveButtons[i].draw(window);
        }
    }
    else
    {
        for (int i = 0; i < _loadButtons.size(); i++)
        {
            _loadButtons[i].draw(window);
        }
    }
}

