#include "Menu.h"
#include "SaveLoad.h"

using namespace sf;
using namespace std;

Menu::Menu(SoundManager& sounds) : _sounds(sounds)
{
    _font.loadFromFile("ITCAvantGardePro-Md.ttf");

    _title.setFont(_font);
    _title.setCharacterSize(80);
    _title.setFillColor(Color::White);
    _title.setOutlineColor(Color::Red);
    _title.setOutlineThickness(2);
    _title.setString("Connect 4");

    FloatRect bounds = _title.getLocalBounds();
    _title.setOrigin(bounds.width / 2, bounds.height / 2);
    _title.setPosition(WINDOW_WIDTH / 2, 50);

    vector<string> labels = { "Jouer", "Classement", "Comment jouer", "Réglages", "Quitter" };

    for (int i = 0; i < labels.size(); i++)
    {
        _buttons.push_back(Button(MAIN_BX, START_Y_MAIN_BUTTON + SPACING * i, MAIN_BX + 5, START_Y_MAIN_BUTTON + SPACING * i, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, labels[i], _font));
    }
}

void Menu::handleEvent(sf::Event& event, sf::RenderWindow& window, State& state, bool needName)
{
    if (event.type == Event::KeyPressed)
    {
        if (event.key.code == Keyboard::Escape)
        {
            _sounds.play("click");
            state = State::QUIT_MENU;
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        Vector2i mousePos = sf::Mouse::getPosition(window);

        for (int i = 0; i < _buttons.size(); i++)
        {
            if (_buttons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                if (i == 0)
                {
                    _sounds.play("click");
                    state = LOAD_MENU;
                }
                else if (i == 1)
                {
                    _sounds.play("click");
                    state = LEADERBOARD;
                }
                else if (i == 2)
                {
                    _sounds.play("click");
                    state = HOW_TO;
                }
                else if (i == 3)
                {
                    _sounds.play("click");
                }
                else if (i == 4)
                {
                    _sounds.play("click");
                    state = QUIT_MENU;
                }
            }
        }
    }
    
}

void Menu::hover(sf::RenderWindow& window)
{
    Vector2i mousePos = sf::Mouse::getPosition(window);

    for (int i = 0; i < _buttons.size(); i++)
    {
        bool isHovered = _buttons[i].getGlobalBounds().contains(mousePos.x, mousePos.y);

        if (isHovered)
        {
            _buttons[i].setFillColor(Color(255, 255, 0, 225));
            _buttons[i].setScale(1.05f, 1.05f);
            _buttons[i].setTextScale(1.05f, 1.05f);

            if (!_buttons[i].wasHovered())
            {
                _sounds.play("hover");
            }
        }
        else
        {
            _buttons[i].setFillColor(Color(255, 255, 255, 175));
            _buttons[i].setScale(1.f, 1.f);
            _buttons[i].setTextScale(1.f, 1.f);
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
