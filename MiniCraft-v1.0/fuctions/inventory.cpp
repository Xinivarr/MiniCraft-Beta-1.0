#include "inventory.h"

#include <iostream>

using namespace std;

void displayInventory(const Player &player)
{
    cout << "\n=== Envanter ===\n";
    if (player.inventory.empty())
    {
        cout << "Envanter bos.\n";
    }
    else
    {
        for (auto &i : player.inventory)
        {
            cout << i.first << " : " << i.second << "\n";
        }
    }
    cout << "================\n";
}

