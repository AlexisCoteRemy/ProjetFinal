#pragma once
#include <string>
#include <map>
//cleaned

class Localization
{
public:
    Localization();

    void setLanguage(const std::string& lang);
    std::string getLanguage() const;

    std::string get(const std::string& key) const;

private:
    std::string _currentLanguage;

    std::map<std::string, std::string> _fr;
    std::map<std::string, std::string> _en;

    void init();
};