#pragma once
#include "EnemyFactory.h"
#include "MainCharacter.h"
#include "Weapons.h"

class Grotte{
public:
    Grotte();
    Grotte(const Hero&, float);
    vector <Enemy*>& getEnemyList();
    void showEnemies() const;
    void showGrotteName() const;
    int getGrotteLevel() const;
    int getGrotteGold() const;
    bool grottePopulated() const;
    bool isWeaponInGrotte() const;
    Weapon getWeapon();
    ~Grotte();
protected:
    vector <Enemy*> enemies;
    string grotteName;
    int grotteLevel;
    int grotteGold;
    EnemyFactory factory;
    Weapon weaponInCave;
};