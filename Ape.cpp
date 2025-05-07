#include "Ape.h"

Ape::Ape() {}

Ape::Ape(int modifier) {
    navn = "Ape";
    basisHP = 30 * (1 + modifier / 10); // Matches the base HP from Enemy.cpp
    hp = basisHP;
    styrke = 5 * (1 + modifier / 10);   // Matches the strength from Enemy.cpp
    xp = 1000 * (1 + modifier / 10);    // Matches the XP from Enemy.cpp
}

Ape::~Ape() {}