#include "Ape.h"

Ape::Ape() {}

//Creating enemy with attributes relating to the type of enemy
//modifier used to increase difficulty and xp gained from defeating enemy
Ape::Ape(int modifier) {
    navn = modifierNames[modifier]+"Ape";
    float adjustedModifier = newModifier(modifier);
    hp = 30 * adjustedModifier; 
    styrke = 5 * adjustedModifier;   
    xp = 1000 * adjustedModifier;    
}


Ape::~Ape() {}