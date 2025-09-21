#include "save.h"

#include <fstream>

using namespace std;

void savePlayer(const Player &player, const string &filename)
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

bool loadPlayer(Player &player, const string &filename)
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

void deleteSave(const string &filename)
{
    remove(filename.c_str());
}

