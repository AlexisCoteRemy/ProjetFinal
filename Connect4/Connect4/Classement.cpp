#include "Classement.h"
#include <fstream>
#include "mesFonctions.h"

using namespace sf;
using namespace std;

Classement::Classement()
{
    _font.loadFromFile("arial.ttf");

    _title.setFont(_font);
    _title.setString("Classement");
    _title.setCharacterSize(60);
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

    _textBox.setSize(Vector2f(TEXTBOX_W, TEXTBOX_H));
    _textBox.setFillColor(Color(255, 255, 255, 175));
    _textBox.setPosition((WINDOW_WIDTH - WINDOW_HEIGHT) / 2, 120);

    _textBox.setOutlineColor(Color::Red);
    _textBox.setOutlineThickness(2);

    _backButton = Button((WINDOW_WIDTH - BACK_BUTTON_WIDTH) / 2, WINDOW_HEIGHT - 15 - (MAIN_BUTTON_HEIGHT * 2), (WINDOW_WIDTH - BACK_BUTTON_WIDTH) / 2, WINDOW_HEIGHT - 15 - (MAIN_BUTTON_HEIGHT * 2), BACK_BUTTON_WIDTH, 50, "Retour", _font);

    _effacer = Button( 650, WINDOW_HEIGHT - 15 - (MAIN_BUTTON_HEIGHT * 2), 650, WINDOW_HEIGHT - 15 - (MAIN_BUTTON_HEIGHT * 2), BACK_BUTTON_WIDTH + 10, 50, "Effacer", _font);

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
        Vector2i mousePos = sf::Mouse::getPosition(window);

        if (_backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            _clickSound.play();
            state = State::MENU;
        }
        if (_effacer.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            clearLeaderboard("classement.txt");

            _noms.clear();
            _victoires.clear();
            _texts.clear();

            loadScores("classement.txt");
            _clickSound.play();
        }
    }
}

void Classement::hover(sf::RenderWindow& window)
{
    Vector2i mousePos = sf::Mouse::getPosition(window);

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

    bool isHovered2 = _effacer.getGlobalBounds().contains(mousePos.x, mousePos.y);

    if (isHovered2)
    {
        _effacer.setFillColor(Color(255, 255, 0, 225));

        if (!_effacer.wasHovered())
        {
            _hoverSound.play();
        }
    }
    else
    {
        _effacer.setFillColor(Color(255, 255, 255, 175));
    }

    _effacer.setWasHovered(isHovered2);
    _backButton.setWasHovered(isHovered);
}

void Classement::draw(sf::RenderWindow& window)
{
    loadScores("classement.txt");
    window.draw(_title);
    window.draw(_textBox);
    window.draw(_users);
    window.draw(_victories);
    for (int i = 0; i < _texts.size(); i++)
    {
        window.draw(_texts[i]);
    }
    _effacer.draw(window);
    _backButton.draw(window);
}

void Classement::loadScores(std::string nameFile)
{
    ifstream file(nameFile);
    string nom;
    int victoires;

    _noms.clear();
    _victoires.clear();
    _texts.clear();

    while (file >> nom >> victoires)
    {
        _noms.push_back(nom);
        _victoires.push_back(victoires);
    }

    file.close();

    int n = _victoires.size();

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (_victoires[i] < _victoires[j])
            {
                swap(_victoires[i], _victoires[j]);
                swap(_noms[i], _noms[j]);
            }
        }
    }

    for (int i = 0; i < _noms.size(); i++)
    {
        Text nomText;
        nomText.setFont(_font);
        nomText.setString(_noms[i]);
        nomText.setCharacterSize(25);
        nomText.setFillColor(sf::Color::Black);
        nomText.setPosition(150, 180 + i * 30);


        Text scoreText;
        scoreText.setFont(_font);
        scoreText.setString(to_string(_victoires[i]));
        scoreText.setCharacterSize(25);
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setPosition(550, 180 + i * 30);

        _texts.push_back(nomText);
        _texts.push_back(scoreText);
    }

}