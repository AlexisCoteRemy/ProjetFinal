#pragma once

#include <SFML/Graphics.hpp>
#include "grid.h"
#include "Joueur.h"
//cleaned

void addUser(std::string nameFile, std::string username);

void updateVictory(std::string nameFile, std::string username);

void clearLeaderboard(std::string nameFile);