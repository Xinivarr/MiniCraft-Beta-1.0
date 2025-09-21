#include "mine.h"

#include <iostream>
#include <string>
#include <cstdlib>

#include "../ui.h"

using namespace std;

void runMine(Player &player)
{
    player.location = "Maden";
    while (true)
    {
        string input;
        int depth = 0;

        input = promptLine("\nMaden derinligi seciniz (-100 ile 100) | Cikmak icin 0: ");

        if (input.empty())
            continue;

        try
        {
            depth = stoi(input);
        }
        catch (...)
        {
            cout << "Gecersiz giris!\n";
            continue;
        }

        if (depth == 0)
        {
            cout << "Madenden cikiliyor...\n";
            break;
        }

        if (depth < -100 || depth > 100)
        {
            cout << "Hatali derinlik!\n";
            continue;
        }

        string foundMine;
        int xpEarned = 0;
        int r = rand() % 100 + 1;

        if (depth <= -70)
        {
            if (r <= 50)
                foundMine = "Elmas", xpEarned = 10 + rand() % 6;
            else if (r <= 80)
                foundMine = "Zumrut", xpEarned = 8 + rand() % 5;
            else if (r <= 95)
                foundMine = "Altin", xpEarned = 5 + rand() % 3;
            else
                foundMine = "Demir", xpEarned = 2 + rand() % 3;
        }
        else if (depth <= -40)
        {
            if (r <= 40)
                foundMine = "Altin", xpEarned = 5 + rand() % 5;
            else if (r <= 70)
                foundMine = "Demir", xpEarned = 3 + rand() % 4;
            else if (r <= 90)
                foundMine = "Kömür", xpEarned = 2;
            else
                foundMine = "Tas", xpEarned = 1;
        }
        else if (depth <= -20)
        {
            if (r <= 50)
                foundMine = "Kömür", xpEarned = 2;
            else if (r <= 80)
                foundMine = "Bakir", xpEarned = 3;
            else
                foundMine = "Tas", xpEarned = 1;
        }
        else if (depth <= 0)
        {
            if (r <= 70)
                foundMine = "Tas", xpEarned = 1;
            else
                foundMine = "Toprak", xpEarned = 1;
        }
        else
        {
            foundMine = "Odun";
            xpEarned = 1;
        }

        player.inventory[foundMine]++;
        player.experience += xpEarned;

        while (player.experience >= 100)
        {
            player.experience -= 100;
            player.level++;
        }

        cout << "\nDerinlik: " << depth
             << " | Bulunan: " << foundMine
             << " | XP +" << xpEarned
             << " | Envanter: " << foundMine
             << " x" << player.inventory[foundMine] << "\n";

        waitEnter();
    }
}
