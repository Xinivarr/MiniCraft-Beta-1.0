#pragma once

#include "../structs/player.h"

// Baslik ekranini ve varsa kayitli oyuncunun durumunu gosterir
void showTitle(const Player *player, bool hasSave);

// Oyun icin ana menu dongusu
// Oyundan cikinca kayit alir ve hasSave'i true yapar.
void runGame(Player &player, bool &hasSave);

