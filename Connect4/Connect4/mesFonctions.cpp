#include "mesFonctions.h"
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void addUser(std::string nameFile, std::string username)
{
    ifstream fileIn(nameFile);
    string user;
    int victories;

    while (fileIn >> user >> victories)
    {
        if (user == username)
        {
            fileIn.close();
            return;
        }
    }

    fileIn.close();

    ofstream fileOut(nameFile, ios::app);

    fileOut << username << " " << 0 << endl;

    fileOut.close();
}

void updateVictory(std::string nameFile, std::string username)
{
    ifstream fileIn(nameFile);
    map<string, int> users;
    string user;
    int victories;

    while (fileIn >> user >> victories)
    {
        users[user] = victories;
    }

    fileIn.close();

    users[username]++;

    ofstream fileOut(nameFile);

    for (auto it = users.begin(); it != users.end(); it++)
    {
        fileOut << it->first << " " << it->second << endl;
    }

    fileOut.close();
}

void clearLeaderboard(std::string nameFile)
{
    ofstream fileOut(nameFile, ios::out | ios::trunc);
    fileOut.close();
}

