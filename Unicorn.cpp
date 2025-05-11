#include "Unicorn.h"

Unicorn::Unicorn() {}

//Creating enemy with attributes relating to the type of enemy
//modifier used to increase difficulty and xp gained from defeating enemy
Unicorn::Unicorn(int modifier) {
    navn = modifierNames[modifier]+"Unicorn";
    float adjustedModifier = newModifier(modifier);
    hp = 5 * adjustedModifier;
    styrke = 8 * adjustedModifier; 
    xp = 1500 * adjustedModifier;   
}

Unicorn::~Unicorn() {}