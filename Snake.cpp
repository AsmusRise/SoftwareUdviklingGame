#include "Snake.h"

Snake::Snake() {}

Snake::Snake(int modifier) {
    navn = "Snake";
    basisHP = 10 * (1 + modifier / 10); // Matches the base HP from Enemy.cpp
    hp = basisHP;
    styrke = 3 * (1 + modifier / 10);  // Matches the strength from Enemy.cpp
    xp = 400 * (1 + modifier / 10);    // Matches the XP from Enemy.cpp
    modifierName = modifierNames[modifier];
}

string Snake::getName(){
    return modifierName + navn;
}

Snake::~Snake() {}