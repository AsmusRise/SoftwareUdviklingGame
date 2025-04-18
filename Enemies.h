using namespace std;
#include <string>
#include <iostream>
#include <vector>
#include "Enemy.h"

class Enemies{
public: 
    Enemies();
    Enemies(vector<Enemy*>);
    void printNames();
    void addEnemy(Enemy*);
    Enemy* getEnemy(const string&);
    ~Enemies();
private:
    vector<Enemy*> enemies;
};

