#include "Dragon.h"

Dragon::Dragon() {}

//Creating enemy with attributes relating to the type of enemy
//modifier used to increase difficulty and xp gained from defeating enemy
Dragon::Dragon(int modifier) {
    navn = modifierNames[modifier]+"Dragon";
    float adjustedModifier = newModifier(modifier);
    hp = 100 * adjustedModifier;
    styrke = 10 * adjustedModifier;  
    xp = 30000 * adjustedModifier;    
}


Dragon::~Dragon() {}