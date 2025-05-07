#include "Dragon.h"

Dragon::Dragon() {}

Dragon::Dragon(int modifier) {
    navn = "Dragon";
    basisHP = 100 * (1 + modifier / 10); // Matches the base HP from Enemy.cpp
    hp = basisHP;
    styrke = 10 * (1 + modifier / 10);   // Matches the strength from Enemy.cpp
    xp = 3000 * (1 + modifier / 10);    // Matches the XP from Enemy.cpp
    modifierName = modifierNames[modifier];
}

string Dragon::getName(){
    return modifierName + navn;
}

Dragon::~Dragon() {}