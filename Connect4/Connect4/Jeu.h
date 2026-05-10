#pragma once

#include <SFML/Graphics.hpp>
#include "Joueur.h"
#include "SoundManager.h"
#include "Button.h"
#include "State.h"
#include "mesConstantes.h"
#include "Grid.h"
#include "FallingToken.h"
#include "Localization.h"
#include "mesFonctions.h"
#include <fstream>

//cleaned
class Jeu
{
public:
	Jeu(Joueur& joueur, SoundManager& sounds, Localization& loc);

	void handleEvent(sf::Event& event, sf::RenderWindow& window, State& state);
	void hover(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void reset();
	void saveGame();
	bool loadGame();
	void update(State& state);
	void updateTurnText();
	void updateTexts();
	bool hasSave();
	
private:
	bool _gamerOver;
	bool _gameStarted;
	bool _blinkState;
	bool _hasSave;
	int _winner;
	bool _waitingForLeaderboard;
	sf::Clock _endClock;
	Joueur& _joueur;
	Grid _grid;
	sf::Text _winText;
	sf::Font _font;
	Button _backButton;
	sf::Clock _blink;
	sf::Clock _clock;

	SoundManager& _sounds;

	FallingToken _fallingToken;

	Localization& _loc;
};
