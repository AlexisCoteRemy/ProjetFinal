#include "mesFonctions.h"
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void centerText(sf::Text& text, float x, float y)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top);
    text.setPosition(x, y);
}

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
