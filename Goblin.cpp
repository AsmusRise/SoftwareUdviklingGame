#include "Goblin.h"

Goblin::Goblin() {}

Goblin::Goblin(int modifier) {
    navn = "Goblin";
    int adjustedModifier = newModifier(modifier);
    basisHP = 4 * adjustedModifier; // Matches the base HP from Enemy.cpp
    hp = basisHP;
    styrke = 2 * adjustedModifier;  // Matches the strength from Enemy.cpp
    xp = 200 * adjustedModifier;    // Matches the XP from Enemy.cpp
    modifierName = modifierNames[modifier];
}

string Goblin::getName(){
    return modifierName + navn;
}

Goblin::~Goblin() {}