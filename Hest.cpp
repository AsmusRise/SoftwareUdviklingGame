#include "Hest.h"

Hest::Hest(){}

//Creating enemy with attributes relating to the type of enemy
//modifier used to increase difficulty and xp gained from defeating enemy
Hest::Hest(int modifier) {
    navn = modifierNames[modifier]+"Hest";
    float adjustedModifier = newModifier(modifier);
    hp = 4 * adjustedModifier;
    styrke = 1 * adjustedModifier;
    xp = 100 * adjustedModifier;
}


Hest::~Hest(){}