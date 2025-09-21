#include "village.h"

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <random>

#include "../ui.h"
#include "../save.h"

using namespace std;

static mt19937 &rng()
{
    static mt19937 gen(random_device{}());
    return gen;
}

static int randint(int lo, int hi)
{
    uniform_int_distribution<int> dist(lo, hi);
    return dist(rng());
}

static void traderMenu(Player &player)
{
    while (true)
    {
        clearScreen();
        cout << "\n=== Tuccar ===\n";
        cout << "1 : Yemek (+10 Can) - $15\n";
        cout << "2 : Iksir (+25 Can) - $30\n";
        cout << "9 : Madenleri Toplu Sat\n";
        cout << "0 : Geri Don\n";
        cout << "Seciminiz: ";

        string s; getline(cin, s);
        int sel = -1; try { sel = stoi(s); } catch (...) { sel = -1; }

        if (sel == 0)
        {
            cout << "Tuccardan ayrildiniz.\n";
            waitEnter();
            return;
        }

        if (sel == 1 || sel == 2)
        {
            int cost = (sel == 1 ? 15 : 30);
            int heal = (sel == 1 ? 10 : 25);
            if (player.money < cost)
            {
                cout << "Yetersiz bakiye! ($" << player.money << ")\n";
                waitEnter();
                continue;
            }
            if (player.health >= 100)
            {
                cout << "Caniniz zaten tam.\n";
                waitEnter();
                continue;
            }
            player.money -= cost;
            player.health = min(100, player.health + heal);
            cout << "Satin alindi! Yeni can: " << player.health << ", Bakiye: $" << player.money << "\n";
            waitEnter();
            continue;
        }

        if (sel == 9)
        {
            // Madenlerden elde edilenleri satalim
            map<string, int> prices = {
                {"Toprak", 1}, {"Tas", 1}, {"Odun", 2}, {"Kömür", 3}, {"Bakir", 4},
                {"Demir", 6}, {"Altin", 10}, {"Zumrut", 20}, {"Elmas", 30}
            };

            int earned = 0;
            for (auto &pp : prices)
            {
                auto it = player.inventory.find(pp.first);
                if (it != player.inventory.end() && it->second > 0)
                {
                    earned += it->second * pp.second;
                    it->second = 0;
                }
            }
            if (earned > 0)
            {
                player.money += earned;
                cout << "Esya satildi! Kazanc: $" << earned << ", Bakiye: $" << player.money << "\n";
            }
            else
            {
                cout << "Satilacak maden yok.\n";
            }
            waitEnter();
            continue;
        }

        cout << "Gecersiz secim!\n";
        waitEnter();
    }
}

static bool plunderVillage(Player &player)
{
    int roll = randint(1, 100);
    if (roll <= 60)
    {
        int moneyGain = randint(20, 60);
        int xpGain = randint(10, 20);
        player.money += moneyGain;
        player.experience += xpGain;
        while (player.experience >= 100)
        {
            player.experience -= 100;
            player.level++;
        }
        cout << "Koyu yagmaladin! $" << moneyGain << " | XP +" << xpGain << "\n";
        return true;
    }
    else
    {
        int dmg = randint(10, 25);
        player.health = max(0, player.health - dmg);
        cout << "Yagmala sirasinda yakalandin! Hasar: -" << dmg << ". Kalan can: " << player.health << "\n";
        if (player.health <= 0)
        {
            cout << "Caniniz tukenmis! Oyun siliniyor.\n";
            deleteSave();
            return false;
        }
        return true;
    }
}

static bool saveVillageAction(Player &player)
{
    // Basit olay: %70 basari, odul; aksi halde hasar
    int roll = randint(1, 100);
    if (roll <= 70)
    {
        int moneyGain = randint(25, 50);
        int xpGain = randint(20, 40);
        player.money += moneyGain;
        player.experience += xpGain;
        while (player.experience >= 100)
        {
            player.experience -= 100;
            player.level++;
        }
        cout << "Koyu kurtardin! Halk minnettar. $" << moneyGain << " | XP +" << xpGain << "\n";
        return true;
    }
    else
    {
        int dmg = randint(5, 20);
        player.health = max(0, player.health - dmg);
        cout << "Saldiranlar guclu ciktiginda yaralandin! Hasar: -" << dmg << ". Kalan can: " << player.health << "\n";
        if (player.health <= 0)
        {
            cout << "Caniniz tukenmis! Oyun siliniyor.\n";
            deleteSave();
            return false;
        }
        return true;
    }
}

bool runVillage(Player &player)
{
    player.location = "Koy";
    while (true)
    {
        clearScreen();
        player.displayStatus();

        cout << "\n=== Koy Merkezi ===\n";
        cout << "1 : Tuccara Git\n";
        cout << "2 : Koyu Yagmala (Lv 5+)\n";
        cout << "3 : Koyu Kurtar (Lv 3+)\n";
        cout << "0 : Geri Don\n";
        cout << "Seciminiz: ";

        string s; getline(cin, s);
        int sel = -1; try { sel = stoi(s); } catch (...) { sel = -1; }

        switch (sel)
        {
        case 0:
            cout << "Koyden ayriliyorsunuz...\n";
            waitEnter();
            return true;
        case 1:
            traderMenu(player);
            break;
        case 2:
        {
            if (player.level < 5)
            {
                cout << "Yagmala icin en az Level 5 gerekir!\n";
                waitEnter();
                break;
            }
            bool ok = plunderVillage(player);
            waitEnter();
            if (!ok) return false;
            break;
        }
        case 3:
        {
            if (player.level < 3)
            {
                cout << "Kurtarmak icin en az Level 3 gerekir!\n";
                waitEnter();
                break;
            }
            bool ok = saveVillageAction(player);
            waitEnter();
            if (!ok) return false;
            break;
        }
        default:
            cout << "Gecersiz secim!\n";
            waitEnter();
            break;
        }
    }
}
