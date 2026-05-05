#pragma once

#include <SFML/Graphics.hpp>
//cleaned

class Joueur
{
public:
	Joueur();

	void setPlayerName(sf::String playerName);
	void setPlayer1Name(sf::String player1Name);
	void setPlayer2Name(sf::String player2Name);
	void setPlayerString(sf::String playerName);
	void setCurrentInputPlayer(int currentInputPlayer);
	void setJoueurAcutel(int joueurActuel);

	void addCharToName(char c);
	void removeLastChar();

	sf::String getPlayerName() const;
	sf::String getPlayer1Name() const;
	sf::String getPlayer2Name() const;

	int getJoueurActuel() const;
	int getCurrentInputPlayer() const;

private:
	sf::String _playerName;
	sf::String _player1Name;
	sf::String _player2Name;
	sf::Text _player;

	int _joueurActuel;
	int _currentInputPlayer;
};