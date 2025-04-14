#pragma once
using namespace std;
#include <iostream>
#include <string>
#include <vector>

class Hero{
public: 
    Hero();
    void createHero(string name);
    void loadHero(string name);
    int attack();
    void levelUp();
    void gainXP(int XP);
    ~Hero();
private:
    string navn;
    int xp;
    int level;
    int styrke;
    vector<string> heroes = {};
};