#include "Settings.h"

using namespace std;

Settings::Settings(SoundManager& sounds, MusicManager& music) : _sounds(sounds), _music(music)
{
    _font.loadFromFile("ITCAvantGardePro-Md.ttf");

    _title.setFont(_font);
    _title.setCharacterSize(60);
    _title.setFillColor(Color::White);
    _title.setOutlineColor(Color::Red);
    _title.setOutlineThickness(2);
    _title.setString("Réglages");

    FloatRect bounds = _title.getLocalBounds();
    _title.setOrigin(bounds.width / 2, bounds.height / 2);
    _title.setPosition(WINDOW_WIDTH / 2, 50);

    _textBox.setSize(Vector2f(TEXTBOX_W, TEXTBOX_H));
    _textBox.setFillColor(Color(255, 255, 255, 175));
    _textBox.setPosition((WINDOW_WIDTH - TEXTBOX_W) / 2, (WINDOW_HEIGHT - TEXTBOX_H) / 2);

    _textBox.setOutlineColor(Color::Red);
    _textBox.setOutlineThickness(2);

    std::vector<string> labels = { "Effets sonores", "Musique" };

    for (int i = 0; i < labels.size(); i++)
    {
        sf::Text text;

        text.setFont(_font);
        text.setCharacterSize(24);
        text.setFillColor(Color::Black);
        text.setOutlineColor(Color::White);
        text.setOutlineThickness(2);

        text.setString(labels[i]);

        float x = _textBox.getPosition().x + 20;
        float y = _textBox.getPosition().y + 20 + i * 60;

        text.setPosition(x, y);

        _labels.push_back(text);

        float buttonY = y;

        float minusX = x + 250;
        float plusX = x + 320;

        _volMinusButtons.push_back(Button(minusX, buttonY, minusX, buttonY, 60, 40, "-", _font));

        _volPlusButtons.push_back(Button(plusX, buttonY, plusX, buttonY, 60, 40, "+", _font));
    }

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

        for (int i = 0; i < _labels.size(); i++)
        {
            if (_volPlusButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                if (i == 0)
                {
                    _sounds.setVolume(_sounds.getVolume() + 5.f);
                }
                else if (i == 1)
                {
                    _music.setVolume(_music.getVolume() + 5.f);
                }

                _sounds.play("click");
            }

            if (_volMinusButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                if (i == 0)
                {
                    _sounds.setVolume(_sounds.getVolume() - 5.f);
                }
                else if (i == 1)
                {
                    _music.setVolume(_music.getVolume() - 5.f);
                }

                _sounds.play("click");
            }
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

    for (int i = 0; i < _labels.size(); i++)
    {
        bool isHovered2 = _volPlusButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y);

        if (isHovered2)
        {
            _volPlusButtons[i].setFillColor(Color(255, 255, 0, 225));
            _volPlusButtons[i].setScale(1.05f, 1.05f);
            _volPlusButtons[i].setTextScale(1.05f, 1.05f);

            if (!_volPlusButtons[i].wasHovered())
            {
                _sounds.play("hover");
            }
        }
        else
        {
            _volPlusButtons[i].setFillColor(Color(255, 255, 255, 175));
            _volPlusButtons[i].setScale(1.f, 1.f);
            _volPlusButtons[i].setTextScale(1.f, 1.f);
        }

        _volPlusButtons[i].setWasHovered(isHovered2);
    }

    for (int i = 0; i < _labels.size(); i++)
    {
        bool isHovered3 = _volMinusButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y);

        if (isHovered3)
        {
            _volMinusButtons[i].setFillColor(Color(255, 255, 0, 225));
            _volMinusButtons[i].setScale(1.05f, 1.05f);
            _volMinusButtons[i].setTextScale(1.05f, 1.05f);

            if (!_volMinusButtons[i].wasHovered())
            {
                _sounds.play("hover");
            }
        }
        else
        {
            _volMinusButtons[i].setFillColor(Color(255, 255, 255, 175));
            _volMinusButtons[i].setScale(1.f, 1.f);
            _volMinusButtons[i].setTextScale(1.f, 1.f);
        }

        _volMinusButtons[i].setWasHovered(isHovered3);
    }
}

void Settings::draw(sf::RenderWindow& window)
{
    window.draw(_title);
    window.draw(_textBox);
    _backButton.draw(window);

    for (int i = 0; i < _labels.size(); i++)
    {
        window.draw(_labels[i]);
        _volMinusButtons[i].draw(window);
        _volPlusButtons[i].draw(window);
    }

    for (int i = 0; i < _labels.size(); i++)
    {
        window.draw(_labels[i]);
    }
}