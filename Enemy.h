#pragma once
using namespace std;
#include <string>
#include <iostream>
#include <vector>

class Enemy{
public:
    Enemy();
    virtual string getName();
    int angrib();
    void tagSkade(int);
    void setHP();
    int getXP();
    bool erDoed();
    int getStyrke();
    int getHP();
    virtual ~Enemy();
protected:
    string navn;
    int basisHP;
    int hp;
    int styrke;
    int xp;
    vector <string> modifierNames;
    string modifierName;
};