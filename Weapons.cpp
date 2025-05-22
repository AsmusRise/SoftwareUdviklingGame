#include "Weapons.h"
Weapon::Weapon(){
    holdbarhed = 0; //used for seing if weapon is valid
}

Weapon::Weapon(string n, int s, int sM, int h){
    name = n;
    skade = s;
    styrkeModifier = sM;
    holdbarhed = h;
}

int Weapon::getSkade() const{
    return skade;
}

string Weapon::getName() const{
    return name;
}

int Weapon::getStyrkeModifier()const {
    return styrkeModifier;
}

int Weapon::getHoldbarhed() const{
    return holdbarhed;
}

void Weapon::use(){
    holdbarhed --;
}

bool Weapon::hasHolbarhed(){
    return holdbarhed>0;
}

Weapon::~Weapon(){}