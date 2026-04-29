#include "CommentJouer.h"

using namespace sf;

CommentJouer::CommentJouer()
{
    _font.loadFromFile("ITCAvantGardePro-Md.ttf");

    _title.setFont(_font);
    _title.setCharacterSize(60);
    _title.setString("Comment jouer");
    _title.setFillColor(Color::White);
    _title.setOutlineColor(Color::Red);
    _title.setOutlineThickness(2);

    FloatRect bounds = _title.getLocalBounds();
    _title.setOrigin(bounds.width / 2, bounds.height / 2);
    _title.setPosition(WINDOW_WIDTH / 2, 50);

    _textBox.setSize(Vector2f(TEXTBOX_W, TEXTBOX_H));
    _textBox.setFillColor(Color(255, 255, 255, 175));
    _textBox.setPosition((WINDOW_WIDTH - TEXTBOX_W) / 2, (WINDOW_HEIGHT - TEXTBOX_H) / 2);

    _textBox.setOutlineColor(Color::Red);
    _textBox.setOutlineThickness(2);

    _texte.setString("Appuyez sur les cercles blancs en haut de la grille\npour faire tomber un jeton.\n\nLes jetons rouges sont pour le premier joueur, et les\njetons jaunes sont pour le deuxieme joueur.\n\nLe premier joueur à aligner quatre jetons dans\nn'importe quelle direction gagne!\n\nBonne chance, et rappelez-vous, c'est un jeu!");
    _texte.setFont(_font);
    _texte.setCharacterSize(22);
    _texte.setPosition(Vector2f(((WINDOW_WIDTH - TEXTBOX_W) + 10) / 2, 120));
    _texte.setFillColor(Color::Black);
    _texte.setOutlineColor(Color::White);
    _texte.setOutlineThickness(0.5);
    _texte.setOutlineColor(Color::White);
    _texte.setOutlineThickness(2);

    _backButton = Button((WINDOW_WIDTH - BACK_BUTTON_WIDTH) / 2, (WINDOW_HEIGHT + 20 - (MAIN_BUTTON_HEIGHT * 2)), (WINDOW_WIDTH - BACK_BUTTON_WIDTH) / 2, (WINDOW_HEIGHT + 20 - (MAIN_BUTTON_HEIGHT * 2)), BACK_BUTTON_WIDTH + 10, 50, "Retour", _font);

    _hoverBuffer.loadFromFile("hoverSound.wav");
    _hoverSound.setBuffer(_hoverBuffer);
    _hoverSound.setVolume(20);

    _clickBuffer.loadFromFile("clickSound.wav");
    _clickSound.setBuffer(_clickBuffer);
    _clickSound.setVolume(20);

    _backBuffer.loadFromFile("backSound.wav");
    _backSound.setBuffer(_backBuffer);
    _backSound.setVolume(20);
}

void CommentJouer::handleEvent(sf::Event& event, sf::RenderWindow& window, State& state)
{
    if (event.type == Event::KeyPressed)
    {
        if (event.key.code == Keyboard::Escape)
        {
            _backSound.play();
            state = State::MENU;
        }
    }

    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
    {
        Vector2i mousePos = sf::Mouse::getPosition(window);

        if (_backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            _backSound.play();
            state = State::MENU;
        }
    }
}

void CommentJouer::hover(sf::RenderWindow& window)
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

    _backButton.setWasHovered(isHovered);
}

void CommentJouer::draw(sf::RenderWindow& window)
{
    window.draw(_title);
    window.draw(_textBox);
    window.draw(_texte);
    _backButton.draw(window);
}