#include "ui.h"

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void waitEnter()
{
    cout << "Devam etmek icin Enter'a basin...";
    cin.get();
}

string promptLine(const string &prompt)
{
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

