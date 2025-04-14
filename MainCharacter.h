#pragma once
using namespace std;
#include <iostream>
#include <string>
#include <vector>

class Hero{
public: 
    Hero();
    Hero();
    void createHero(string name);
    void setName();
    void chooseHero();
    int attack();
    void levelUp();
    void gainXP(int XP);
    void initializeHeroes();
    void showHeroes();
    ~Hero();
private:
    string navn;
    int xp;
    int level;
    int styrke;
    int hp;
    vector<string> heroes = {};
};