#include "Joueur.h"

Joueur::Joueur()
{
	_playerName = "";
	_player1Name = "";
	_player2Name = "";

	_joueurActuel = 1;
	_currentInputPlayer = 1;
}

void Joueur::setPlayerName(sf::String playerName)
{
	_playerName = playerName;
}

void Joueur::setPlayer1Name(sf::String player1Name)
{
	_player1Name = player1Name;
}

void Joueur::setPlayer2Name(sf::String player2Name)
{
	_player2Name = player2Name;
}

void Joueur::setPlayerString(sf::String playerName)
{
	_player.setString(playerName);
}

void Joueur::setCurrentInputPlayer(int currentInputPlayer)
{
	_currentInputPlayer = currentInputPlayer;
}

void Joueur::setJoueurAcutel(int joueurActuel)
{
	_joueurActuel = joueurActuel;
}

void Joueur::addCharToName(char c)
{
	_playerName += c;
}

void Joueur::removeLastChar()
{
	if (!_playerName.isEmpty())
	{
		_playerName.erase(_playerName.getSize() - 1);
	}
}

sf::String Joueur::getPlayerName() const
{
	return _playerName;
}

sf::String Joueur::getPlayer1Name() const
{
	return _player1Name;
}

sf::String Joueur::getPlayer2Name() const
{
	return _player2Name;
}

int Joueur::getJoueurActuel() const
{
	return _joueurActuel;
}

int Joueur::getCurrentInputPlayer() const
{
	return _currentInputPlayer;
}

