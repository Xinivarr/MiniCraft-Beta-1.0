#include "player.h"

#include <iostream>

using namespace std;

void Player::displayStatus() const
{
    cout << name << " | ❤️ " << health
         << " | Level " << level
         << " | XP " << static_cast<int>(experience)
         << " | $" << money
         << " | Konum: " << location << "\n";
}

