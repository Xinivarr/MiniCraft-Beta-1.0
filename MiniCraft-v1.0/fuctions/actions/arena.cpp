#include "arena.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "../ui.h"
#include "../save.h"

using namespace std;

bool runArena(Player &player)
{
    player.location = "Arena";
    int arenaLife = 3;
    vector<string> opponents = {"Goblin", "Orc", "Troll", "Vampir", "Savasci", "Haydut"};

    while (arenaLife > 0)
    {
        string opponent = opponents[rand() % opponents.size()];
        int opponentLife = rand() % 5 + 3;

        cout << "\nRakip: " << opponent << " | Can: " << opponentLife
             << "\nSenin arenadaki canin: " << arenaLife
             << "\nSavasmak icin 1, cikmak icin 0: ";
        int sel = -1;
        {
            string s;
            getline(cin, s);
            try { sel = stoi(s); } catch (...) { sel = -1; }
        }

        if (sel == 0)
        {
            cout << "Arenadan cikiliyor...\n";
            break;
        }
        if (sel != 1)
        {
            cout << "Hatali secim!\n";
            continue;
        }

        while (opponentLife > 0 && arenaLife > 0)
        {
            int square = rand() % 9 + 1;
            cout << "1-9 arasinda bir kare seciniz: ";
            int playerChoice = -1;
            {
                string s;
                getline(cin, s);
                try { playerChoice = stoi(s); } catch (...) { playerChoice = -1; }
            }

            if (playerChoice == square)
            {
                opponentLife--;
                cout << "Dogru kare! Rakibin 1 can kaybetti. Kalan: " << opponentLife << "\n";
            }
            else
            {
                arenaLife--;
                cout << "Yanlis kare! Arenadaki canin 1 azaldi. Kalan: " << arenaLife << "\n";
            }
        }

        if (arenaLife <= 0)
        {
            cout << "Arenadaki caniniz tukenmis! Ana caninizdan 10 eksildi.\n";
            player.health = max(0, player.health - 10);
            if (player.health <= 0)
            {
                cout << "Ana caniniz tukenmis! Oyun siliniyor.\n";
                deleteSave();
                return false; // oyun sonlansin
            }
            else
            {
                cout << "Yeniden arenaya donmek icin Enter'a basin...";
                waitEnter();
                arenaLife = 3;
                continue;
            }
        }

        if (opponentLife <= 0)
        {
            int moneyReward = 20 + rand() % 31;
            int xpReward = 50 + rand() % 51;
            player.money += moneyReward;
            player.experience += xpReward;
            while (player.experience >= 100)
            {
                player.experience -= 100;
                player.level++;
            }
            cout << "Rakibi yendiniz! $" << moneyReward << " / XP +" << xpReward << "\n";
        }
    }

    cout << "Arena sona erdi. ";
    waitEnter();
    return true;
}
