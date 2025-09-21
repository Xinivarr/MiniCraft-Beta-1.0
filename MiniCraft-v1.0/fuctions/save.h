#pragma once

#include <string>
#include "../structs/player.h"

void savePlayer(const Player &player, const std::string &filename = "save.txt");
bool loadPlayer(Player &player, const std::string &filename = "save.txt");
void deleteSave(const std::string &filename = "save.txt");

