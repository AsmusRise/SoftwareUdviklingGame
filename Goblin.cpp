#include "Goblin.h"

Goblin::Goblin() {}

//Creating enemy with attributes relating to the type of enemy
//modifier used to increase difficulty and xp gained from defeating enemy
Goblin::Goblin(int modifier) {
    navn = modifierNames[modifier]+"Goblin";
    float adjustedModifier = newModifier(modifier);
    hp = 4 * adjustedModifier;
    styrke = 2 * adjustedModifier;  
    xp = 200 * adjustedModifier;    
}


Goblin::~Goblin() {}