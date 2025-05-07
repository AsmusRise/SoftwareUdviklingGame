#include "Unicorn.h"

Unicorn::Unicorn() {}

Unicorn::Unicorn(int modifier) {
    navn = "Unicorn";
    basisHP = 5 * (1 + modifier / 10); // Matches the base HP from Enemy.cpp
    hp = basisHP;
    styrke = 8 * (1 + modifier / 10);  // Matches the strength from Enemy.cpp
    xp = 1500 * (1 + modifier / 10);   // Matches the XP from Enemy.cpp
    modifierName = modifierNames[modifier];
}

string Unicorn::getName(){
    return modifierName + navn;
}

Unicorn::~Unicorn() {}