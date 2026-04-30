#include "Settings.h"

using namespace std;

Settings::Settings(SoundManager& sounds) : _sounds(sounds)
{
    _font.loadFromFile("ITCAvantGardePro-Md.ttf");

    _title.setFont(_font);
    _title.setCharacterSize(80);
    _title.setFillColor(Color::White);
    _title.setOutlineColor(Color::Red);
    _title.setOutlineThickness(2);
    _title.setString("Réglages");

    FloatRect bounds = _title.getLocalBounds();
    _title.setOrigin(bounds.width / 2, bounds.height / 2);
    _title.setPosition(WINDOW_WIDTH / 2, 50);

    _backButton = Button((WINDOW_WIDTH - BACK_BUTTON_WIDTH) / 2, (WINDOW_HEIGHT + 20 - (MAIN_BUTTON_HEIGHT * 2)), (WINDOW_WIDTH - BACK_BUTTON_WIDTH) / 2, (WINDOW_HEIGHT + 20 - (MAIN_BUTTON_HEIGHT * 2)), BACK_BUTTON_WIDTH + 10, 50, "Retour", _font);
}

void Settings::handleEvent(sf::Event& event, sf::RenderWindow& window, State& state)
{
    if (event.type == Event::KeyPressed)
    {
        if (event.key.code == Keyboard::Escape)
        {
            _sounds.play("back");
            state = MENU;
        }
    }

    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
    {
        Vector2i mousePos = sf::Mouse::getPosition(window);

        if (_backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            _sounds.play("back");
            state = State::MENU;
        }
    }
}

void Settings::hover(sf::RenderWindow& window)
{
    Vector2i mousePos = sf::Mouse::getPosition(window);

    bool isHovered = _backButton.getGlobalBounds().contains(mousePos.x, mousePos.y);

    if (isHovered)
    {
        _backButton.setFillColor(Color(255, 255, 0, 225));
        _backButton.setScale(1.05f, 1.05f);
        _backButton.setTextScale(1.05f, 1.05f);

        if (!_backButton.wasHovered())
        {
            _sounds.play("hover");
        }
    }
    else
    {
        _backButton.setFillColor(Color(255, 255, 255, 175));
        _backButton.setScale(1.f, 1.f);
        _backButton.setTextScale(1.f, 1.f);
    }

    _backButton.setWasHovered(isHovered);
}

void Settings::draw(sf::RenderWindow& window)
{
    window.draw(_title);
    _backButton.draw(window);
}