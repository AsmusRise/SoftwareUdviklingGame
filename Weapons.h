using namespace std;
#pragma once
#include <string>
#include <iostream>

class Weapon
{
protected:
    string name;
    int skade;
    int styrkeModifier;
    int holdbarhed;
    vector <string> killList; //used to see if a weapon has been used to kill an enemy
public:
    Weapon();
    Weapon(string n, int s, int sM, int h);

    //get metoder
    int getSkade() const;
    string getName() const;
    int getStyrkeModifier() const;
    int getHoldbarhed() const;

    void addToKillList(string);

    void use(); //decreases holbarhed
    bool hasHolbarhed();
    ~Weapon();
};