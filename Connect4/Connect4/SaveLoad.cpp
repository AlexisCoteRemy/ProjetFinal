#include "SaveLoad.h"
#include "mesConstantes.h"
#include "mesFonctions.h"
#include <fstream>

using namespace std;

SaveLoad::SaveLoad()
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

    _hoverBuffer.loadFromFile("hoverSound.wav");
    _hoverSound.setBuffer(_hoverBuffer);
    _hoverSound.setVolume(10);

    _clickBuffer.loadFromFile("clickSound.wav");
    _clickSound.setBuffer(_clickBuffer);
    _clickSound.setVolume(10);
}

void SaveLoad::handleEvent(sf::Event& event, sf::RenderWindow& window, State& state, bool& wantSave, bool& wantLoad, Jeu& jeu)
{
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
                        _clickSound.play();
                        state = GAME;
                    }
                    else if (i == 1)
                    {
                        jeu.saveGame();
                        _clickSound.play();
                    }
                    else if (i == 2)
                    {
                        _clickSound.play();
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
                        _clickSound.play();
                        jeu.reset();
                        state = NAME_INPUT;
                    }
                    else if (i == 1)
                    {
                        bool hasGame = jeu.loadGame();
                        _clickSound.play();

                        if (hasGame)
                        {
                            state = GAME;
                        }
                        else
                            warning.draw(window);
                    }
                    else if (i == 2)
                    {
                        _clickSound.play();
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

                if (!_saveButtons[i].wasHovered())
                {
                    _hoverSound.play();
                }
            }
            else
            {
                _saveButtons[i].setFillColor(Color(255, 255, 255, 175));
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

                if (!_loadButtons[i].wasHovered())
                {
                    _hoverSound.play();
                }
            }
            else
            {
                _loadButtons[i].setFillColor(Color(255, 255, 255, 175));
            }

            _loadButtons[i].setWasHovered(isHovered);
        }
    }
}

void SaveLoad::draw(sf::RenderWindow& window,State& state)
{
    window.draw(_title);

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
