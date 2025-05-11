#pragma once
using namespace std;
#include <string>
#include <iostream>
#include <vector>
#include "Enemy.h"
#include <algorithm>
#include "Hest.h"
#include "Goblin.h"
#include "Snake.h"
#include "Ape.h"
#include "Dragon.h"
#include "Unicorn.h"


class EnemyFactory{
public:
    EnemyFactory();

    //creating enemy with name of enemy and modifier (from one to length of modifiernames)
    Enemy* createEnemy(string n, int m);

    //creating list of enemies which will populate cave
    //based on hero attributes /strength of hero.
    vector <Enemy*> createEnemyList(float att, float hp); 
    ~EnemyFactory();
protected:
    vector<string> modifierNames; //list for names describing strenght of enemy
    vector<string> enemyNames; //list of base names which enemies can have.
};
