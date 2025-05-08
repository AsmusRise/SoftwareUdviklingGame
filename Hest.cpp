#include "Hest.h"

Hest::Hest(){}

Hest::Hest(int modifier) {
    navn = "Hest";
    int adjustedModifier = newModifier(modifier);
    basisHP = 4 * adjustedModifier;
    hp = basisHP;
    styrke = 1 * adjustedModifier;
    xp = 100 * adjustedModifier;
    modifierName = modifierNames[modifier];
}



string Hest::getName(){
    return modifierName + navn;
}

int Hest::getStyrke(){
    return styrke;
}

Hest::~Hest(){}