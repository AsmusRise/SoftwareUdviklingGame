#include "Hest.h"

Hest::Hest(){}

Hest::Hest(int modifier) {
    navn = modifierNames[modifier]+"Hest";
    float adjustedModifier = newModifier(modifier);
    //cout << "Modifier: " << modifier << " And adjusted modifier: " << adjustedModifier << endl;
    basisHP = 4 * adjustedModifier;
    hp = basisHP;
    styrke = 1 * adjustedModifier;
    xp = 100 * adjustedModifier;
}


Hest::~Hest(){}