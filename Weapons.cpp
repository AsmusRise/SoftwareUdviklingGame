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
    holdbarhed =holdbarhed-1;
    cout << "Weapon used, new holdbarhed: " << getHoldbarhed() << endl;
}

bool Weapon::hasHolbarhed(){
    return holdbarhed>0;
}

void Weapon::addToKillList(string enemyName){
    killList.push_back(enemyName);
}

Weapon::~Weapon(){}