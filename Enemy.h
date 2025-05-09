#pragma once
using namespace std;
#include <string>
#include <iostream>
#include <vector>

class Enemy{
public:
    Enemy();
    virtual string getName();
    float angrib();
    void tagSkade(float);
    void setHP();
    float getXP();
    bool erDoed();
    virtual float getStyrke();
    float getHP();
    float newModifier(float);
    virtual ~Enemy();
protected:
    string navn;
    float basisHP;
    float hp;
    float styrke;
    float xp;
    vector <string> modifierNames;
    string modifierName;
};