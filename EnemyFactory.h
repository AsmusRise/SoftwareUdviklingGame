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
    Enemy* createEnemy(string n, int m);
    vector <Enemy*> createEnemyList(int, int);
    ~EnemyFactory();
protected:
    vector<string> modifierNames;
    vector<string> enemyNames;
};
