
#include <fstream>

#include "Classement.h"


#include "mesFonctions.h"

using namespace sf;
using namespace std;

//cleaned
Classement::Classement(SoundManager& sounds, Localization& loc) : _sounds(sounds), _loc(loc)
{
    _font.loadFromFile("ITCAvantGardePro-Md.ttf");

    _title.setFont(_font);
    _title.setString(_loc.get("leader.title"));
    _title.setCharacterSize(60);
    _title.setFillColor(Color::White);
    _title.setOutlineColor(Color::Red);
    _title.setOutlineThickness(2);

    FloatRect bounds = _title.getLocalBounds();
    _title.setOrigin(bounds.width / 2, bounds.height / 2);
    _title.setPosition(WINDOW_WIDTH / 2, 50);

    _users.setFont(_font);
    _users.setString(_loc.get("leader.users"));
    _users.setCharacterSize(40);
    _users.setFillColor(Color::Black);
    _users.setOutlineColor(Color::White);
    _users.setOutlineThickness(2);
    _users.setPosition((TEXTBOX_W / 2) / 2, 120);

    _victories.setFont(_font);
    _victories.setString(_loc.get("leader.victories"));
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

    _backButton = Button((WINDOW_WIDTH - BACK_BUTTON_WIDTH) / 2, WINDOW_HEIGHT + 20 - (MAIN_BUTTON_HEIGHT * 2), (WINDOW_WIDTH - BACK_BUTTON_WIDTH) / 2, WINDOW_HEIGHT + 20 - (MAIN_BUTTON_HEIGHT * 2), BACK_BUTTON_WIDTH + 10, 50, _loc.get("global.back"), _font);

    _effacer = Button(650, WINDOW_HEIGHT + 20 - (MAIN_BUTTON_HEIGHT * 2), 650, WINDOW_HEIGHT + 20 - (MAIN_BUTTON_HEIGHT * 2), BACK_BUTTON_WIDTH + 20, 50, _loc.get("leader.clear"), _font);

    _offset = 0;
    _maxVisible = 8;

    _arrowTexture.loadFromFile("arrow.png");

    _upArrow.setTexture(_arrowTexture);
    _downArrow.setTexture(_arrowTexture);

    sf::FloatRect bounds2 = _upArrow.getLocalBounds();
    _upArrow.setOrigin(bounds2.width / 2, bounds2.height / 2);
    _downArrow.setOrigin(bounds2.width / 2, bounds2.height / 2);

    _upArrow.setRotation(0);
    _downArrow.setRotation(180);

    _upArrow.setPosition(((WINDOW_WIDTH - TEXTBOX_W) / 2) + TEXTBOX_W - 50, ((WINDOW_HEIGHT - TEXTBOX_H) / 2) + 100);
    _downArrow.setPosition(((WINDOW_WIDTH - TEXTBOX_W) / 2) + TEXTBOX_W - 50, ((WINDOW_HEIGHT - TEXTBOX_H) / 2) + TEXTBOX_H - 30);
}

void Classement::handleEvent(sf::Event& event, sf::RenderWindow& window, State& state)
{
    if (event.type == Event::KeyPressed)
    {
        if (event.key.code == Keyboard::Escape)
        {
            _sounds.play("back");
            state = State::MENU;
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
        if (_effacer.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            clearLeaderboard("classement.txt");
            loadScores("classement.txt");
            _sounds.play("click");
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

    bool isHovered2 = _effacer.getGlobalBounds().contains(mousePos.x, mousePos.y);

    if (isHovered2)
    {
        _effacer.setFillColor(Color(255, 255, 0, 225));
        _effacer.setScale(1.05f, 1.05f);
        _effacer.setTextScale(1.05f, 1.05f);

        if (!_effacer.wasHovered())
        {
            _sounds.play("hover");
        }
    }
    else
    {
        _effacer.setFillColor(Color(255, 255, 255, 175));
        _effacer.setScale(1.f, 1.f);
        _effacer.setTextScale(1.f, 1.f);
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

    if (_offset > 0)
    {
        window.draw(_upArrow);
    }

    if (_offset + _maxVisible < _noms.size())
    {
        window.draw(_downArrow);
    }

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
        row.setSize(Vector2f(TEXTBOX_W - 120, 30));
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
        
        if (index == 0)
        {
            nomText.setFillColor(Color(255, 215, 0, 255));
            nomText.setOutlineThickness(2);
            nomText.setOutlineColor(Color::Black);
        }
            
        else if (index == 1)
        {
            nomText.setOutlineThickness(2);
            nomText.setOutlineColor(Color::Black);
            nomText.setFillColor(Color(192, 192, 192, 255));
        }
            
        else if (index == 2)
        {
            nomText.setOutlineThickness(2);
            nomText.setOutlineColor(Color::Black);
            nomText.setFillColor(Color(205, 127, 50, 255));
        }
            
        else
        {
            nomText.setFillColor(Color::Black);
            nomText.setOutlineColor(Color::White);
            nomText.setOutlineThickness(2);
        }  
        
        nomText.setPosition((TEXTBOX_W / 2) / 2, 180 + i * 30);

        Text scoreText;
        scoreText.setFont(_font);
        scoreText.setString(to_string(_victoires[index]));
        scoreText.setCharacterSize(25);

        if (index == 0)
        {
            scoreText.setOutlineThickness(2);
            scoreText.setOutlineColor(Color::Black);
            scoreText.setFillColor(Color(255, 215, 0, 255));
        }
            
        else if (index == 1)
        {
            scoreText.setFillColor(Color(192, 192, 192, 255));
            scoreText.setOutlineThickness(2);
            scoreText.setOutlineColor(Color::Black);
        }
            
        else if (index == 2)
        {
            scoreText.setFillColor(Color(205, 127, 50, 255));
            scoreText.setOutlineThickness(2);
            scoreText.setOutlineColor(Color::Black);
        }
            
        else
        {
            scoreText.setFillColor(Color::Black);
            scoreText.setOutlineColor(Color::White);
            scoreText.setOutlineThickness(2);
        }

        scoreText.setPosition((TEXTBOX_W / 2) + (TEXTBOX_W / 4) + (TEXTBOX_W / 8), 180 + i * 30);

        _texts.push_back(nomText);
        _texts.push_back(scoreText);
    }
}

void Classement::updateTexts()
{
    _title.setString(_loc.get("leader.title"));

    FloatRect bounds = _title.getLocalBounds();
    _title.setOrigin(bounds.width / 2, bounds.height / 2);
    _title.setPosition(WINDOW_WIDTH / 2, 50);

    _users.setString(_loc.get("leader.users"));
    _victories.setString(_loc.get("leader.victories"));

    _backButton.setText(_loc.get("global.back"));
    _effacer.setText(_loc.get("leader.clear"));
}