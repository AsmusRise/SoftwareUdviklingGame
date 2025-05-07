#include "Hest.h"

Hest::Hest(){}

Hest::Hest(int modifier) {
    navn = "Hest";
    basisHP = 4 * (1 + modifier / 10);
    hp = basisHP;
    styrke = 1 * (1 + modifier / 10);
    xp = 100 * (1 + modifier / 10);
    modifierName = modifierNames[modifier];
}

string Hest::getName(){
    return modifierName + navn;
}

Hest::~Hest(){}