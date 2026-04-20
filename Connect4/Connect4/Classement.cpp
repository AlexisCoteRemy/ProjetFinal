#include "Classement.h"

using namespace sf;

Classement::Classement()
{
    _font.loadFromFile("arial.ttf");

    _title.setFont(_font);
    _title.setString("Classement");
    _title.setCharacterSize(50);
    _title.setFillColor(Color::White);
    _title.setOutlineColor(Color::Red);
    _title.setOutlineThickness(2);

    FloatRect bounds = _title.getLocalBounds();
    _title.setOrigin(bounds.width / 2, bounds.height / 2);
    _title.setPosition(WINDOW_WIDTH / 2, 50);

    _users.setFont(_font);
    _users.setString("Utilisateurs");
    _users.setCharacterSize(40);
    _users.setFillColor(Color::Black);
    _users.setOutlineColor(Color::White);
    _users.setOutlineThickness(2);
    _users.setPosition(125, 120);

    _victories.setFont(_font);
    _victories.setString("Victoires");
    _victories.setCharacterSize(40);
    _victories.setFillColor(Color::Black);
    _victories.setOutlineColor(Color::White);
    _victories.setOutlineThickness(2);
    _victories.setPosition(500, 120);

    _textBox.setSize(Vector2f(600, 350));
    _textBox.setFillColor(Color(255, 255, 255, 175));
    _textBox.setPosition((WINDOW_WIDTH - 600) / 2, 120);

    _textBox.setOutlineColor(Color::Red);
    _textBox.setOutlineThickness(2);

    _backButton = Button((WINDOW_WIDTH - BACK_BUTTON_WIDTH) / 2, WINDOW_HEIGHT - (MAIN_BUTTON_HEIGHT * 2), (WINDOW_WIDTH - BACK_BUTTON_WIDTH) / 2, WINDOW_HEIGHT - (MAIN_BUTTON_HEIGHT * 2), BACK_BUTTON_WIDTH, 50, "Retour", _font);

    _hoverBuffer.loadFromFile("hoverSound.wav");
    _hoverSound.setBuffer(_hoverBuffer);
    _hoverSound.setVolume(10);

    _clickBuffer.loadFromFile("clickSound.wav");
    _clickSound.setBuffer(_clickBuffer);
    _clickSound.setVolume(10);
}

void Classement::handleEvent(sf::Event& event, sf::RenderWindow& window, State& state)
{
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (_backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            _clickSound.play();
            state = State::MENU;
        }
    }
}

void Classement::hover(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    bool isHovered = _backButton.getGlobalBounds().contains(mousePos.x, mousePos.y);

    if (isHovered)
    {
        _backButton.setFillColor(Color(255, 255, 0, 225));

        if (!_backButton.wasHovered())
        {
            _hoverSound.play();
        }
    }
    else
    {
        _backButton.setFillColor(Color(255, 255, 255, 175));
    }

    _backButton.setWasHovered(isHovered);
}

void Classement::draw(sf::RenderWindow& window)
{
    window.draw(_title);
    window.draw(_textBox);
    window.draw(_users);
    window.draw(_victories);
    _backButton.draw(window);
}
