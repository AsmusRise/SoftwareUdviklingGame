#include "Dragon.h"

Dragon::Dragon() {}

Dragon::Dragon(int modifier) {
    navn = "Dragon";
    int adjustedModifier = newModifier(modifier);
    basisHP = 100 * adjustedModifier; // Matches the base HP from Enemy.cpp
    hp = basisHP;
    styrke = 10 * adjustedModifier;   // Matches the strength from Enemy.cpp
    xp = 3000 * adjustedModifier;    // Matches the XP from Enemy.cpp
    modifierName = modifierNames[modifier];
}

string Dragon::getName(){
    return modifierName + navn;
}

Dragon::~Dragon() {}