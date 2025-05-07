#pragma once
using namespace std;
#include <iostream>
#include <string>
#include <vector>

class Hero{
public: 
    Hero();
    void createHero(string name);
    void setName();
    void chooseHero();
    int attack();
    void takeDamage(int);
    void levelUp();
    void gainXP(int XP);
    void initializeHeroes();
    void showHeroes();

    //get metoder:
    string getName();
    int getXP();
    int getLevel();
    int getStyrke();
    int getHP();
    void getStats();

    //set metoder:
    void setHP(int);
    void setStyrke(int);
    bool erDoed();
    ~Hero();
    
private:
    string navn;
    int xp;
    int level;
    int styrke;
    int hp;
    int baseHP;
    vector<string> heroes = {};
};