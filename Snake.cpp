#include "Snake.h"

Snake::Snake() {}

//Creating enemy with attributes relating to the type of enemy
//modifier used to increase difficulty and xp gained from defeating enemy
Snake::Snake(int modifier) {
    float adjustedModifier = newModifier(modifier);
    navn = modifierNames[modifier]+"Snake";
    hp = 10 * adjustedModifier; 
    styrke = 3 * adjustedModifier;  
    xp = 400 * adjustedModifier;    
}

Snake::~Snake() {}