#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <map>
#include <limits>

using namespace std;

struct Player
{
    string name;
    int health;
    int level;
    double experience;
    int money;
    string location;
    map<string, int> inventory;

    void displayStatus() const
    {
        cout << name << " | ❤️ " << health
             << " | Level " << level
             << " | XP " << static_cast<int>(experience)
             << " | $" << money
             << " | Konum: " << location << "\n";
    }
};

void savePlayer(const Player &player, const string &filename = "save.txt")
{
    ofstream file(filename);
    if (file.is_open())
    {
        file << player.name << '\n'
             << player.health << '\n'
             << player.level << '\n'
             << player.experience << '\n'
             << player.money << '\n'
             << player.location << '\n';
        file.close();
    }
}

bool loadPlayer(Player &player, const string &filename = "save.txt")
{
    ifstream file(filename);
    if (!file.is_open())
        return false;

    getline(file, player.name);
    file >> player.health >> player.level >> player.experience >> player.money;
    file.ignore();
    getline(file, player.location);
    file.close();
    return true;
}

void deleteSave(const string &filename = "save.txt")
{
    remove(filename.c_str());
}

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

int main()
{
    srand(time(0));
    Player player;
    bool hasSave = loadPlayer(player);

    while (true)
    {
        system("clear");
        cout << "          |=============================================================|\n";
        cout << "          |                        Mini Craft                           |\n";
        cout << "          |=============================================================|\n";
        cout << "          |                Version 1.0 | by: [Xinivar]                  |\n";
        cout << "          |info Komudu Ile Oyun Ve Yapimcilar Hakkinda Bilgi Alabilirsin|\n";
        cout << "          |=============================================================|\n";

        if (hasSave)
        {
            cout << "Kayitli oyuncu bulundu: " << player.name << "\n";
            cout << "Durum: ";
            player.displayStatus();
        }

        cout << "\n    ===Ana Menu===\n";
        cout << "   1 : Oyunu Baslat\n";
        if (hasSave)
            cout << "   2 : Kaydi Sil\n";
        cout << "   0 : Cikis Yap\n";
        cout << "   info : Oyun Hakkinda Bilgi Al\n";
        cout << "\n   Seciminiz: ";

        string input;
        getline(cin, input);

        if (input == "info")
        {
            system("clear");
            cout << "================ Oyun Hakkinda | INFO ================\n";
            cout << "Mini Craft Version 1.0\n";
            cout << "Yapimci: [Xinivar]\n";
            cout << "Tum Haklar Saklidir | E9K.com.tr\n";
            cout << "================ Oyun Rehberi | INFO ================\n";
            cout << "Devam etmek icin Enter'a basin...";
            cin.get();
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

            bool gameRunning = true;
            while (gameRunning)
            {
                system("clear");
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
                try
                {
                    choice = stoi(input);
                }
                catch (...)
                {
                    choice = -1;
                }

                switch (choice)
                {
                case 1: // Madene git
                {
                    player.location = "Maden";
                    while (true)
                    {
                        string input;
                        int depth = 0;

                        cout << "\nMaden derinligi seciniz (-100 ile 100) | Cikmak icin 0: ";
                        getline(cin, input);

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

                        cout << "Devam etmek icin Enter'a basin...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    break;
                }

                case 2:
                    player.location = "Ev";
                    cout << "\nEve gittiniz!\nDevam etmek icin Enter'a basin...";
                    cin.get();
                    break;

                case 3:
                    player.location = "Koy";
                    cout << "\nKoye gittiniz!\nDevam etmek icin Enter'a basin...";
                    cin.get();
                    break;

                case 5:
                    displayInventory(player);
                    cout << "Devam etmek icin Enter'a basin...";
                    cin.get();
                    break;

                case 4: // Arena
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
                        int sel;
                        cin >> sel;
                        cin.ignore();
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
                            int playerChoice;
                            cout << "1-9 arasinda bir kare seciniz: ";
                            cin >> playerChoice;
                            cin.ignore();

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
                                gameRunning = false;
                                break;
                            }
                            else
                            {
                                cout << "Yeniden arenaya donmek icin Enter'a basin...";
                                cin.get();
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
                    cout << "Arena sona erdi. Devam etmek icin Enter'a basin...";
                    cin.get();
                    break;
                }

                case 6:
                    cout << "\nOyundan cikiliyor ve kaydediliyor...\n";
                    savePlayer(player);
                    gameRunning = false;
                    hasSave = true;
                    break;

                default:
                    cout << "\nGecersiz secim!\nDevam etmek icin Enter'a basin...";
                    cin.get();
                }
            }
            hasSave = true;
        }
        else if (input == "2" && hasSave)
        {
            deleteSave();
            hasSave = false;
            cout << "Kayit silindi!\nDevam etmek icin Enter'a basin...";
            cin.get();
        }
        else if (input == "0")
        {
            cout << "Cikis yapiliyor...\n";
            break;
        }
        else
        {
            cout << "Gecersiz secim!\nDevam etmek icin Enter'a basin...";
            cin.get();
        }
    }

    return 0;
}
