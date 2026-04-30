#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Joueur.h"
#include "SoundManager.h"
#include "Button.h"
#include "State.h"
#include "mesConstantes.h"
#include "Grid.h"

class Jeu
{
public:
	Jeu(Joueur& joueur, SoundManager& sounds);

	void handleEvent(sf::Event& event, sf::RenderWindow& window, State& state);
	void hover(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void reset();
	void saveGame();
	bool loadGame();
	void update(State& state);
	
private:
	bool _gamerOver;
	bool _gameStarted;
	bool _blinkState;
	int _winner;
	bool _waitingForLeaderboard;
	sf::Clock _endClock;
	Joueur& _joueur;
	Grid _grid;
	sf::Text _winText;
	sf::Font _font;
	Button _backButton;
	sf::Clock _blink;

	SoundManager& _sounds;

protected:
	void backButtonPressed(State& state);
};
