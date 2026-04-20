#include "Menu.h"

using namespace sf;
using namespace std;

Menu::Menu()
{
    _font.loadFromFile("arial.ttf");

    _title.setFont(_font);
    _title.setCharacterSize(80);
    _title.setFillColor(Color::White);
    _title.setOutlineColor(Color::Red);
    _title.setOutlineThickness(2);
    _title.setString("Connect4");

    FloatRect bounds = _title.getLocalBounds();
    _title.setOrigin(bounds.width / 2, bounds.height / 2);
    _title.setPosition(WINDOW_WIDTH / 2, 50);

    std::vector<string> labels = { "Jouer", "Classement", "Comment joueur", "Quitter" };

    for (int i = 0; i < labels.size(); i++)
    {
        _buttons.push_back(Button(MAIN_BX, START_Y_MAIN_BUTTON + SPACING * i, MAIN_BX, START_Y_MAIN_BUTTON + SPACING * i, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, labels[i], _font));
    }

    _hoverBuffer.loadFromFile("hoverSound.wav");
    _hoverSound.setBuffer(_hoverBuffer);
    _hoverSound.setVolume(10);

    _clickBuffer.loadFromFile("clickSound.wav");
    _clickSound.setBuffer(_clickBuffer);
    _clickSound.setVolume(10);
}

void Menu::handleEvent(sf::Event& event, sf::RenderWindow& window, State& state, bool needName)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        for (int i = 0; i < _buttons.size(); i++)
        {
            if (_buttons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                if (i == 0)
                {
                    if (needName)
                    {
                        _clickSound.play();
                        state = NAME_INPUT;
                    }
                    else
                    {
                        _clickSound.play();
                        state = GAME;
                    }
                }
                else if (i == 1)
                {
                    _clickSound.play();
                    state = LEADERBOARD;
                }
                else if (i == 2)
                {
                    _clickSound.play();
                    state = HOW_TO;
                }
                else if (i == 3)
                {
                    window.close();
                }
            }
        }
    }
}

void Menu::hover(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    for (int i = 0; i < _buttons.size(); i++)
    {
        bool isHovered = _buttons[i].getGlobalBounds().contains(mousePos.x, mousePos.y);

        if (isHovered)
        {
            _buttons[i].setFillColor(Color(255, 255, 0, 225));

            if (!_buttons[i].wasHovered())
            {
                _hoverSound.play();
            }
        }
        else
        {
            _buttons[i].setFillColor(Color(255, 255, 255, 175));
        }

        _buttons[i].setWasHovered(isHovered);
    }
}

void Menu::draw(sf::RenderWindow& window)
{
    window.draw(_title);

    for (int i = 0; i < _buttons.size(); i++)
    {
        _buttons[i].draw(window);
    }
}
