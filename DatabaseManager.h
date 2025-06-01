#pragma once
#include "MainCharacter.h"
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <string>

class DatabaseManager{
public:
    DatabaseManager();
    void initDatabase();
    void showHeroesFromDatabase();
    void deleteHeroByName(const string& heroName);
    void saveHeroInDatabase(Hero& hero);
    Hero loadHeroFromDatabase(const string& heroName);

    //sql commands showing what task requires:
    void showHeroesAlphabetically();
    void showNumberOfEnemiesDefeated();
    void showKillByWeaponForHero(string);
    void showHeroMostKillsUniqueWeapon();


    ~DatabaseManager();
};

