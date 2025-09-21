#include "game.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdlib>

#include "ui.h"
#include "save.h"
#include "inventory.h"

using namespace std;

static void runMine(Player &player)
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

// false dondururse oyun sonlandirilmali (oyuncu olum cezasi)
static bool runArena(Player &player)
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

void showTitle(const Player *player, bool hasSave)
{
    cout << "          |=============================================================|\n";
    cout << "          |                        Mini Craft                           |\n";
    cout << "          |=============================================================|\n";
    cout << "          |                Version 1.0 | by: [Xinivar]                  |\n";
    cout << "          |info Komudu Ile Oyun Ve Yapimcilar Hakkinda Bilgi Alabilirsin|\n";
    cout << "          |=============================================================|\n";

    if (hasSave && player)
    {
        cout << "Kayitli oyuncu bulundu: " << player->name << "\n";
        cout << "Durum: ";
        player->displayStatus();
    }
}

void runGame(Player &player, bool &hasSave)
{
    bool gameRunning = true;
    while (gameRunning)
    {
        clearScreen();
        player.displayStatus();

        cout << "\nAna Menu:\n";
        cout << "1 : Madene Git\n";
        cout << "2 : Eve Git\n";
        cout << "3 : Koye Git\n";
        cout << "4 : Arenaya Git\n";
        cout << "5 : Envanteri Gosterir\n";
        cout << "6 : Oyundan Cikar\n";
        cout << "\nSeciminiz: ";

        string input;
        int choice;

        getline(cin, input);
        try { choice = stoi(input); } catch (...) { choice = -1; }

        switch (choice)
        {
        case 1:
            runMine(player);
            break;
        case 2:
            player.location = "Ev";
            cout << "\nEve gittiniz! ";
            waitEnter();
            break;
        case 3:
            player.location = "Koy";
            cout << "\nKoye gittiniz! ";
            waitEnter();
            break;
        case 5:
            displayInventory(player);
            waitEnter();
            break;
        case 4:
        {
            bool cont = runArena(player);
            if (!cont)
            {
                gameRunning = false;
            }
            break;
        }
        case 6:
            cout << "\nOyundan cikiliyor ve kaydediliyor...\n";
            savePlayer(player);
            gameRunning = false;
            hasSave = true;
            break;
        default:
            cout << "\nGecersiz secim! ";
            waitEnter();
            break;
        }
    }
}

