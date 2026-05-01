#include "Localization.h"

Localization::Localization()
{
    _currentLanguage = "fr";
    init();
}

void Localization::init()
{
    // ===== MENU =====
    _fr["menu.play"] = "Jouer";
    _fr["menu.leaderboard"] = "Classement";
    _fr["menu.howto"] = "Comment jouer";
    _fr["menu.settings"] = "Réglages";
    _fr["menu.quit"] = "Quitter";
    _fr["menu.title"] = "Puissance 4";

    _en["menu.play"] = "Play";
    _en["menu.leaderboard"] = "Leaderboard";
    _en["menu.howto"] = "How to play";
    _en["menu.settings"] = "Settings";
    _en["menu.quit"] = "Quit";
    _en["menu.title"] = "Connect 4";

    // ===== GLOBAL =====
    _fr["global.back"] = "Retour";
    _en["global.back"] = "Back";

    // ===== NAME INPUT =====
    _fr["name.player1"] = "Nom du joueur 1 : ";
    _fr["name.player2"] = "Nom du joueur 2 : ";

    _en["name.player1"] = "Player 1 name: ";
    _en["name.player2"] = "Player 2 name: ";

    // ===== GAME =====
    _fr["game.turn"] = "Tour de ";
    _fr["game.win"] = "Victoire de ";
    _fr["game.draw"] = "Partie nulle !";

    _en["game.turn"] = "Turn of ";
    _en["game.win"] = "Winner is ";
    _en["game.draw"] = "Draw game !";

    // ===== SETTINGS =====
    _fr["settings.sound"] = "Effets sonores";
    _fr["settings.music"] = "Musique";
    _fr["settings.language"] = "Langue";

    _en["settings.sound"] = "Sound effects";
    _en["settings.music"] = "Music";
    _en["settings.language"] = "Language";

    // ===== SAVE / LOAD =====
    _fr["save.continue"] = "Continuer";
    _fr["save.save"] = "Sauvegarder";
    _fr["save.new"] = "Nouvelle";
    _fr["save.load"] = "Charger";
    _fr["save.menu"] = "Menu";
    _fr["save.nosave"] = "Aucune partie sauvegardée";
    _fr["save.saved"] = "Partie sauvegardée";

    _en["save.continue"] = "Continue";
    _en["save.save"] = "Save";
    _en["save.new"] = "New";
    _en["save.load"] = "Load";
    _en["save.menu"] = "Menu";
    _en["save.nosave"] = "No saved game";
    _en["save.saved"] = "Game saved";

    // ===== LEADERBOARD =====
    _fr["leader.users"] = "Utilisateurs";
    _fr["leader.victories"] = "Victoires";
    _fr["leader.clear"] = "Effacer";

    _en["leader.users"] = "Users";
    _en["leader.victories"] = "Wins";
    _en["leader.clear"] = "Clear";

    // ===== HOW TO =====
    _fr["how.text"] =
        "Appuyez sur les cercles blancs en haut de la grille\n"
        "pour faire tomber un jeton.\n\n"
        "Rouge = joueur 1, Jaune = joueur 2.\n\n"
        "Alignez 4 jetons pour gagner !";

    _en["how.text"] =
        "Click the white circles above the grid\n"
        "to drop a token.\n\n"
        "Red = player 1, Yellow = player 2.\n\n"
        "Align 4 tokens to win!";

    // ===== QUIT =====
    _fr["quit.yes"] = "Oui";
    _fr["quit.no"] = "Non";
    _fr["quit.title"] = "Quitter?";

    _en["quit.yes"] = "Yes";
    _en["quit.no"] = "No";
    _en["quit.title"] = "Quit?";
}

void Localization::setLanguage(const std::string& lang)
{
    _currentLanguage = lang;
}

std::string Localization::getLanguage() const
{
    return _currentLanguage;
}

std::string Localization::get(const std::string& key) const
{
    if (_currentLanguage == "fr")
    {
        if (_fr.count(key))
        {
            return _fr.at(key);
        }
    }
    else if (_currentLanguage == "en")
    {
        if (_en.count(key))
        {
            return _en.at(key);
        }
    }

    return "[MISSING:" + key + "]";
}