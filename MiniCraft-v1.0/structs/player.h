#pragma once

#include <string>
#include <map>

struct Player
{
    std::string name;
    int health;
    int level;
    double experience;
    int money;
    std::string location;
    std::map<std::string, int> inventory;

    void displayStatus() const;
};

