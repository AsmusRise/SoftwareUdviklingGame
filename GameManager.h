#pragma once
#include "MainCharacter.h"
#include "Grotte.h"
#include "DatabaseManager.h"

#include <vector>
#include <memory>

class GameManager{
protected:
    DatabaseManager& dbManager; // add databasemanager class
public:
    GameManager(DatabaseManager& dbManager);
    void fightInGrotte(Hero& hero, vector<unique_ptr<Grotte>>& grotter, int& grotteLevel);
    void fight(Hero* hero, Enemy* enemy);
    void startGame(Hero& hero);
    void makeNewCave(Hero& hero, vector<unique_ptr<Grotte>>& grotter, int& grotteLevel);
    ~GameManager();

};