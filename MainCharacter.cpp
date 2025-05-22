#include "MainCharacter.h"

Hero::Hero(){
    heroes = {"August", "Goatie", "Goldielock", "Kaj", "Alfredo"};
    navn = "empty";
    xp = 0;
    level = 1;
    styrke = 2;
    hp = 10;
    baseHP=10;
    gold = 0;
    weapons = {};
}

void Hero::setName(){
    cout << "Choose a name: " << endl;
    cin >> navn;
}

void Hero::chooseHero(){
    while(true){
        cout << "\nShowing heroes: " << endl;
        showHeroes();
        string chooseName;
        cout << "\nChoose hero: ";
        cin >> chooseName;
        for(int i = 0; i < heroes.size(); i++) {
            if (heroes[i] == chooseName) {
                navn = chooseName;
                return;
            }
        }
        cout << "invalid Hero, please choose again " << endl;
    }    
}

int Hero::attack(){
    if(isWeaponEquipped){ //if weapon is equipped, the bonus dmg is added accordingly
        currentWeapon->use();
        return styrke*(1+currentWeapon->getStyrkeModifier()) + currentWeapon->getSkade();
    }
    return styrke;
}

void Hero::takeDamage(int d){
    hp -=d;
}

// Increases the hero's level, base HP, and strength.
// Resets the hero's HP to the new base HP.
void Hero::levelUp(){
    level++;
    baseHP +=2;
    hp = baseHP;
    styrke += 1;
}

// Adds XP to the hero. If the XP exceeds the threshold for the current level,
// the hero levels up, and the excess XP is carried over.
void Hero::gainXP(int XP){
    xp += XP;
    hp = baseHP;
    if(xp>level*1000){
        cout << navn << " er steget i level!!! Viser nye stats: " << endl; 
        xp =xp-level*1000;
        levelUp();
        getStats();
        sleep(2);
    }
}

void Hero::gainGold(int g){
    gold +=g;
}

void Hero::showHeroes(){
    for(int i =0; i<heroes.size(); i++){
        cout << heroes[i] << endl;
    }
}

string Hero::getName() const{
    return navn;
}

int Hero::getXP() const{
    return xp;
}

int Hero::getLevel() const{
    return level;
}

int Hero::getStyrke() const{
    return styrke;
}

int Hero::getHP() const{
    return hp;
}

int Hero::getGold() const{
    return gold;
}

void Hero::getStats() const{
    cout << "\n ---- Hero stats ----" << endl;
            cout << "Name: " << getName() << endl;
            cout << "XP: " << getXP() << endl;
            cout << "Level: " << getLevel() << endl;
            cout << "Styrke: " << getStyrke() << endl;
            cout << "HP: " << getHP() << endl;
            cout << "Gold: " << getGold() << endl;
}

void Hero::setHP(int h){
    hp = h;
}

void Hero::getNewWeapon(Weapon newWeapon){
    weapons.push_back(newWeapon);
}

void Hero::equipWeapon(const Weapon& weapon){
    for(Weapon& w : weapons){
        if(w.getName() == weapon.getName()){
            currentWeapon = &w;
            cout << "Weapon equipped: " << weapon.getName() << endl;
            return;
        }
    }
    cout << "Weapon couldnt be found" << endl;
}

bool Hero::isWeaponEquipped(){
    if(weapons.size()==0){
        return false;
    }
    return currentWeapon->hasHolbarhed();
}

bool Hero::erDoed(){
    return hp<0;
}

Hero::~Hero(){}