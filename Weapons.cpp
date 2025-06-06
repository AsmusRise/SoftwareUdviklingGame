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
    if(this == nullptr){
        cout << "Error: weapon object is null" << endl;
        return;
    }
    cout << "Adding enemy to kill list: " << enemyName << endl;
    cout << "Current kill list size: " << killList.size() << endl;
    if(enemyName.size()>1 && enemyName.size()<50){ //check for valid lengths of enemyname
        killList.push_back(enemyName);
    }
    cout << "New kill list size: " << killList.size() << endl;
}

vector<string> Weapon::getKillList() const{
    return killList;
}

Weapon::~Weapon(){}