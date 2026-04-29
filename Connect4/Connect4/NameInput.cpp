#include "NameInput.h"
#include "mesFonctions.h"

using namespace sf;
using namespace std;

NameInput::NameInput(Joueur& joueur) : _joueur(joueur)
{
	_font.loadFromFile("ITCAvantGardePro-Md.ttf");

	_title.setFont(_font);
	_title.setCharacterSize(60);
	_title.setString("Utilisateurs");
	_title.setFillColor(Color::White);
	_title.setOutlineColor(Color::Red);
	_title.setOutlineThickness(2);

	FloatRect bounds = _title.getLocalBounds();
	_title.setOrigin(bounds.width / 2, bounds.height / 2);
	_title.setPosition(WINDOW_WIDTH / 2, MAIN_BUTTON_HEIGHT);

	_textBox.setSize(Vector2f(TEXTBOX_W, 50));
	_textBox.setFillColor(Color(255, 255, 255, 175));
	_textBox.setPosition((WINDOW_WIDTH - TEXTBOX_W) / 2, 120);
	_textBox.setOutlineColor(Color::Red);
	_textBox.setOutlineThickness(2);

	_texte.setFont(_font);
	_texte.setCharacterSize(30);
	_texte.setPosition(Vector2f(105, 125));
	_texte.setFillColor(Color::Black);
	_texte.setOutlineColor(Color::White);
	_texte.setOutlineThickness(0.5);
	_texte.setOutlineColor(Color::White);
	_texte.setOutlineThickness(2);

	_backButton = Button((WINDOW_WIDTH - BACK_BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - 15 - (MAIN_BUTTON_HEIGHT * 2)), (WINDOW_WIDTH - BACK_BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - 15 - (MAIN_BUTTON_HEIGHT * 2)), BACK_BUTTON_WIDTH + 10, 50, "Retour", _font);

	_hoverBuffer.loadFromFile("hoverSound.wav");
	_hoverSound.setBuffer(_hoverBuffer);
	_hoverSound.setVolume(20);

	_clickBuffer.loadFromFile("clickSound.wav");
	_clickSound.setBuffer(_clickBuffer);
	_clickSound.setVolume(20);

	_backBuffer.loadFromFile("backSound.wav");
	_backSound.setBuffer(_backBuffer);
	_backSound.setVolume(20);

	_keyboardBuffer.loadFromFile("keyboardType.wav");
	_keyboardSound.setBuffer(_keyboardBuffer);
	_keyboardSound.setVolume(10);

	_backspaceBuffer.loadFromFile("backspaceType.wav");
	_backspaceSound.setBuffer(_backspaceBuffer);
	_backspaceSound.setVolume(10);
}

void NameInput::handleEvent(sf::Event& event, sf::RenderWindow& window, State& state)
{
	if (event.type == Event::KeyPressed)
	{
		if (event.key.code == Keyboard::Escape)
		{
			_backSound.play();
			state = State::LOAD_MENU;
		}
	}

	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		Vector2i mousePos = sf::Mouse::getPosition(window);

		if (_backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
		{
			_backSound.play();
			state = State::LOAD_MENU;
		}
	}

	if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode == 8)
		{
			_backspaceSound.play();
			_joueur.removeLastChar();
		}
		else if (event.text.unicode < 128 && event.text.unicode >= 32)
		{
			_keyboardSound.play();
			_joueur.addCharToName(event.text.unicode);
		}

		_joueur.setPlayerString(_joueur.getPlayerName());
	}

	if (event.type == Event::KeyPressed)
	{
		if (event.key.code == Keyboard::Enter)
		{
			if (_joueur.getCurrentInputPlayer() == 1)
			{
				_joueur.setPlayer1Name(_joueur.getPlayerName());
				addUser("classement.txt", _joueur.getPlayerName());
				_joueur.setPlayerName("");
				_joueur.setCurrentInputPlayer(2);
			}
			else
			{
				_joueur.setPlayer2Name(_joueur.getPlayerName());
				addUser("classement.txt", _joueur.getPlayerName());
				state = GAME;
				_joueur.setJoueurAcutel(1);
			}
		}
	}
}

void NameInput::hover(sf::RenderWindow& window)
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
			_hoverSound.play();
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

void NameInput::draw(sf::RenderWindow& window)
{
	window.draw(_title);
	window.draw(_textBox);

	string label;;

	if (_joueur.getCurrentInputPlayer() == 1)
	{
		label = "Nom du joueur 1 : ";
	}
	else
	{
		label = "Nom du joueur 2 : ";
	}

	label += _joueur.getPlayerName();
	_texte.setString(label);
	window.draw(_texte);
	_backButton.draw(window);
}
