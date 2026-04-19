#include "CommentJouer.h"

using namespace sf;

CommentJouer::CommentJouer()
{
    _font.loadFromFile("arial.ttf");

    _title.setFont(_font);
    _title.setCharacterSize(60);
    _title.setString("Comment jouer");
    _title.setFillColor(Color::White);
    _title.setOutlineColor(Color::Red);
    _title.setOutlineThickness(2);

    FloatRect bounds = _title.getLocalBounds();
    _title.setOrigin(bounds.width / 2, bounds.height / 2);
    _title.setPosition(WINDOW_WIDTH / 2, 50);

    _textBox.setSize(Vector2f(600, 350));
    _textBox.setFillColor(Color(255, 255, 255, 175));
    _textBox.setPosition((WINDOW_WIDTH - 600) / 2, 120);

    _textBox.setOutlineColor(Color::Red);
    _textBox.setOutlineThickness(2);

    _texte.setString("\nAppuyez sur les cercles blancs en haut de la grille pour faire \ntomber un jeton.\n\nLes jetons rouges sont pour le premier joueur, et les jetons\njaunes sont pour le deuxieme joueur.\n\nLe premier joueur à aligner quatre jetons dans n'importe\nquelle direction gagne!\n\nBonne chance, et rappelez-vous, c'est un jeu!");
    _texte.setFont(_font);
    _texte.setCharacterSize(20);
    _texte.setPosition(Vector2f((WINDOW_WIDTH - 590) / 2, (WINDOW_HEIGHT - 375) / 2));
    _texte.setFillColor(Color::Black);
    _texte.setOutlineColor(Color::White);
    _texte.setOutlineThickness(0.5);
    _texte.setOutlineColor(Color::White);
    _texte.setOutlineThickness(2);

    _backButton = Button((WINDOW_WIDTH - 125) / 2, 500, (WINDOW_WIDTH - 125) / 2, 500, 125, 50, "Retour", _font);

    _hoverBuffer.loadFromFile("hoverSound.wav");
    _hoverSound.setBuffer(_hoverBuffer);
    _hoverSound.setVolume(10);

    _clickBuffer.loadFromFile("clickSound.wav");
    _clickSound.setBuffer(_clickBuffer);
    _clickSound.setVolume(10);
}

void CommentJouer::handleEvent(sf::Event& event, sf::RenderWindow& window, State& state)
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

void CommentJouer::hover(sf::RenderWindow& window)
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

void CommentJouer::draw(sf::RenderWindow& window)
{
    window.draw(_title);
    window.draw(_textBox);
    window.draw(_texte);
    _backButton.draw(window);
}