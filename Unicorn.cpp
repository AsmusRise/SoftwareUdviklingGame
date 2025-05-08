#include "Unicorn.h"

Unicorn::Unicorn() {}

Unicorn::Unicorn(int modifier) {
    navn = "Unicorn";
    int adjustedModifier = newModifier(modifier);
    basisHP = 5 * adjustedModifier; // Matches the base HP from Enemy.cpp
    hp = basisHP;
    styrke = 8 * adjustedModifier;  // Matches the strength from Enemy.cpp
    xp = 1500 * adjustedModifier;   // Matches the XP from Enemy.cpp
    modifierName = modifierNames[modifier];
}

string Unicorn::getName(){
    return modifierName + navn;
}

Unicorn::~Unicorn() {}