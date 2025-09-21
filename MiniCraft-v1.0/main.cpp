#include <iostream>
#include <string>
#include <ctime>

using namespace std;

#include "structs/player.h"
#include "fuctions/ui.h"
#include "fuctions/game.h"
#include "fuctions/save.h"

int main()
{
    srand(time(0));
    Player player;
    bool hasSave = loadPlayer(player);

    while (true)
    {
        clearScreen();
        showTitle(hasSave ? &player : nullptr, hasSave);

        cout << "\n    ===Ana Menu===\n";
        cout << "   1 : Oyunu Baslat\n";
        if (hasSave) cout << "   2 : Kaydi Sil\n";
        cout << "   0 : Cikis Yap\n";
        cout << "   info : Oyun Hakkinda Bilgi Al\n";
        cout << "\n   Seciminiz: ";

        string input;
        getline(cin, input);

        if (input == "info")
        {
            clearScreen();
            cout << "================ Oyun Hakkinda | INFO ================\n";
            cout << "Mini Craft Version 1.0\n";
            cout << "Yapimci: [Xinivar]\n";
            cout << "Tum Haklar Saklidir | E9K.com.tr\n";
            cout << "================ Oyun Rehberi | INFO ================\n";
            waitEnter();
            continue;
        }

        if (input == "1")
        {
            if (!hasSave)
            {
                cout << "Yeni oyuncu olusturuluyor...\n";
                cout << "Kullanici Adi: ";
                getline(cin, player.name);
                player.health = 100;
                player.level = 1;
                player.experience = 0;
                player.money = 0;
                player.location = "Ev";
            }

            runGame(player, hasSave);
        }
        else if (input == "2" && hasSave)
        {
            deleteSave();
            hasSave = false;
            cout << "Kayit silindi!\n";
            waitEnter();
        }
        else if (input == "0")
        {
            cout << "Cikis yapiliyor...\n";
            break;
        }
        else
        {
            cout << "Gecersiz secim!\n";
            waitEnter();
        }
    }

    return 0;
}

