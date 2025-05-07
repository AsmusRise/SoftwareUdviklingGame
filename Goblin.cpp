#include "Goblin.h"

Goblin::Goblin() {}

Goblin::Goblin(int modifier) {
    navn = "Goblin";
    basisHP = 4 * (1 + modifier / 10); // Matches the base HP from Enemy.cpp
    hp = basisHP;
    styrke = 2 * (1 + modifier / 10);  // Matches the strength from Enemy.cpp
    xp = 200 * (1 + modifier / 10);    // Matches the XP from Enemy.cpp
    modifierName = modifierNames[modifier];
}

string Goblin::getName(){
    return modifierName + navn;
}

Goblin::~Goblin() {}