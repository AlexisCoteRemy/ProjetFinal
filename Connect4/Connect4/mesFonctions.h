#pragma once

#include <SFML/Graphics.hpp>
#include "grid.h"
#include "Joueur.h"

void addUser(std::string nameFile, std::string username);

void updateVictory(std::string nameFile, std::string username);

void clearLeaderboard(std::string nameFile);

void saveGrid(int grid[][7]);

