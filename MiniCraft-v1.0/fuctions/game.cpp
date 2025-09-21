#include "game.h"

#include <iostream>
#include <string>

#include "ui.h"
#include "save.h"
#include "inventory.h"
#include "actions/mine.h"
#include "actions/arena.h"

using namespace std;




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
