#include "Classement.h"
#include <fstream>
#include "mesFonctions.h"

using namespace sf;
using namespace std;

Classement::Classement()
{
    _font.loadFromFile("ITCAvantGardePro-Md.ttf");

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
    _users.setPosition((TEXTBOX_W / 2) / 2, 120);

    _victories.setFont(_font);
    _victories.setString("Victoires");
    _victories.setCharacterSize(40);
    _victories.setFillColor(Color::Black);
    _victories.setOutlineColor(Color::White);
    _victories.setOutlineThickness(2);
    _victories.setPosition((TEXTBOX_W / 2) + (TEXTBOX_W / 4), 120);

    _textBox.setSize(Vector2f(TEXTBOX_W, TEXTBOX_H));
    _textBox.setFillColor(Color(255, 255, 255, 175));
    _textBox.setPosition((WINDOW_WIDTH - TEXTBOX_W) / 2, (WINDOW_HEIGHT - TEXTBOX_H) / 2);

    _textBox.setOutlineColor(Color::Red);
    _textBox.setOutlineThickness(2);

    _backButton = Button((WINDOW_WIDTH - BACK_BUTTON_WIDTH) / 2, WINDOW_HEIGHT + 20 - (MAIN_BUTTON_HEIGHT * 2), (WINDOW_WIDTH - BACK_BUTTON_WIDTH) / 2, WINDOW_HEIGHT + 20 - (MAIN_BUTTON_HEIGHT * 2), BACK_BUTTON_WIDTH + 10, 50, "Retour", _font);

    _effacer = Button(650, WINDOW_HEIGHT + 20 - (MAIN_BUTTON_HEIGHT * 2), 650, WINDOW_HEIGHT + 20 - (MAIN_BUTTON_HEIGHT * 2), BACK_BUTTON_WIDTH + 20, 50, "Effacer", _font);

    _hoverBuffer.loadFromFile("hoverSound.wav");
    _hoverSound.setBuffer(_hoverBuffer);
    _hoverSound.setVolume(10);

    _clickBuffer.loadFromFile("clickSound.wav");
    _clickSound.setBuffer(_clickBuffer);
    _clickSound.setVolume(10);

    _offset = 0;
    _maxVisible = 8;
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
            loadScores("classement.txt");
            _clickSound.play();
        }
    }

    if (event.type == sf::Event::MouseWheelScrolled)
    {
        if (event.mouseWheelScroll.delta > 0)
        {
            _offset--;
        }
        else
        {
            _offset++;
        }

        if (_offset < 0)
        {
            _offset = 0;
        }

        if (_offset > _noms.size() - _maxVisible)
        {
            _offset = _noms.size() - _maxVisible;
        }

        if (_noms.size() < _maxVisible)
        {
            _offset = 0;
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

    if (_noms.empty())
    {
        _effacer.draw(window);
        _backButton.draw(window);
    }

    else
    {

        for (int i = 0; i < _rows.size(); i++)
        {
            window.draw(_rows[i]);
        }

        for (int i = 0; i < _texts.size(); i++)
        {
            window.draw(_texts[i]);
        }
        _effacer.draw(window);
        _backButton.draw(window);
    }
}

void Classement::loadScores(std::string nameFile)
{
    ifstream file(nameFile);
    string nom;
    int victoires;

    _noms.clear();
    _victoires.clear();
    _texts.clear();
    _rows.clear();

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

    int nbLignes;

    if (_noms.size() - _offset < _maxVisible)
    {
        nbLignes = _noms.size() - _offset;
    }
    else
    {
        nbLignes = _maxVisible;
    }

    for (int i = 0; i < nbLignes; i++)
    {
        RectangleShape row;
        row.setSize(Vector2f(TEXTBOX_W - 40, 30));
        row.setPosition((WINDOW_WIDTH - TEXTBOX_W) / 2 + 20, 180 + i * 30);

        if (i % 2 == 0)
        {
            row.setFillColor(Color(255, 0, 0, 50));
        }
        else
        {
            row.setFillColor(Color(255, 255, 0, 50));
        }

        _rows.push_back(row);

        int index = i + _offset;

        if (index >= _noms.size())
        {
            break;
        }
        Text nomText;
        nomText.setFont(_font);
        nomText.setString(_noms[index]);
        nomText.setCharacterSize(25);
        nomText.setFillColor(sf::Color::Black);
        nomText.setPosition((TEXTBOX_W / 2) / 2, 180 + i * 30);


        Text scoreText;
        scoreText.setFont(_font);
        scoreText.setString(to_string(_victoires[index]));
        scoreText.setCharacterSize(25);
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setPosition((TEXTBOX_W / 2) + (TEXTBOX_W / 4) + (TEXTBOX_W / 8), 180 + i * 30);

        _texts.push_back(nomText);
        _texts.push_back(scoreText);
    }

}