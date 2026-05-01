#include "Quit.h"

using namespace std;

Quit::Quit(SoundManager& sounds, Localization& loc) : _sounds(sounds), _loc(loc)
{
    _font.loadFromFile("ITCAvantGardePro-Md.ttf");

    _title.setFont(_font);
    _title.setCharacterSize(80);
    _title.setFillColor(Color::White);
    _title.setOutlineColor(Color::Red);
    _title.setOutlineThickness(2);
    _title.setString(_loc.get("quit.title"));

    FloatRect bounds = _title.getLocalBounds();
    _title.setOrigin(bounds.width / 2, bounds.height / 2);
    _title.setPosition(WINDOW_WIDTH / 2, 50);

    vector<string> labels = { _loc.get("quit.yes"), _loc.get("quit.no")};

    for (int i = 0; i < labels.size(); i++)
    {
        _buttons.push_back(Button(MAIN_BX, START_Y_MAIN_BUTTON + SPACING * i, MAIN_BX + 5, START_Y_MAIN_BUTTON + SPACING * i, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, labels[i], _font));
    }
}

void Quit::handleEvent(sf::Event& event, sf::RenderWindow& window, State& state, State& previousState)
{
    if (event.type == Event::KeyPressed)
    {
        if (event.key.code == Keyboard::Escape)
        {
            _sounds.play("back");
            state = previousState;
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
                    window.close();
                }
                else
                {
                    _sounds.play("back");
                    state = previousState;
                }
            }
        }
    }
}

void Quit::hover(sf::RenderWindow& window)
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

void Quit::draw(sf::RenderWindow& window)
{
    window.draw(_title);

    for (int i = 0; i < _buttons.size(); i++)
    {
        _buttons[i].draw(window);
    }
}

void Quit::updateTexts()
{
    _title.setString(_loc.get("quit.title"));

    FloatRect bounds = _title.getLocalBounds();
    _title.setOrigin(bounds.width / 2, bounds.height / 2);
    _title.setPosition(WINDOW_WIDTH / 2, 50);

    _buttons[0].setText(_loc.get("quit.yes"));
    _buttons[1].setText(_loc.get("quit.no"));
}