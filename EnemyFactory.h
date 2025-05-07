#pragma once
using namespace std;
#include <string>
#include <iostream>
#include <vector>
#include "Enemy.h"
#include <algorithm>


class EnemyFactory{
public:
    EnemyFactory();
    Enemy* createEnemy(string n, int m);
    ~EnemyFactory();
protected:
    vector<string> modifierNames;
    vector<string> enemyNames;
};
