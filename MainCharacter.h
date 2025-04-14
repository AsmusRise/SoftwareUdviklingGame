#pragma once
using namespace std;
#include <iostream>
#include <string>
#include <vector>

class Hero{
public: 
    Hero();
    void createHero(string name);
    void loadHero();
    void chooseHero(string);
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