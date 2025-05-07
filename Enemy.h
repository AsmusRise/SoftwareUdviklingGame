#pragma once
using namespace std;
#include <string>
#include <iostream>
#include <vector>

class Enemy{
public:
    Enemy();
    Enemy(string, int);
    string getName();
    int angrib();
    void tagSkade(int);
    void setHP();
    int getXP();
    bool erDoed();
    int getStyrke();
    int getHP();
    ~Enemy();
public:
    string navn;
    int basisHP;
    int hp;
    int styrke;
    int xp;
};