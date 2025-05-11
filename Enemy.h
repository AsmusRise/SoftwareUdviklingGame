#pragma once
using namespace std;
#include <string>
#include <iostream>
#include <vector>

class Enemy{
public:
    Enemy(); // Default constructor
    virtual string getName();  // Returns the name of the enemy
    float angrib();
    void tagSkade(float);
    float getXP();
    bool erDoed(); // Returns true if the enemy is dead
    virtual float getStyrke(); // Returns the strength of the enemy
    float getHP();
    float newModifier(float); // Adjusts the modifier based on the input
    virtual ~Enemy(); // Destructor
protected:
    string navn;
    float hp;
    float styrke;
    float xp;
    vector <string> modifierNames; // List of names describing the strength of the enemy
    string modifierName; 
};