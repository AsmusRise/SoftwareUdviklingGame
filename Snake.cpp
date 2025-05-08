#include "Snake.h"

Snake::Snake() {}

Snake::Snake(int modifier) {
    int adjustedModifier = newModifier(modifier);
    navn = "Snake";
    basisHP = 10 * adjustedModifier; // Matches the base HP from Enemy.cpp
    hp = basisHP;
    styrke = 3 * adjustedModifier;  // Matches the strength from Enemy.cpp
    xp = 400 * adjustedModifier;    // Matches the XP from Enemy.cpp
    modifierName = modifierNames[modifier];
}

string Snake::getName(){
    return modifierName + navn;
}

Snake::~Snake() {}