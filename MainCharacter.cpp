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
    currentWeapon = nullptr;
}

void Hero::setName(){
    cout << "Choose a name: " << endl;
    cin >> navn;
}

void Hero::setLevel(int lvl){
    level=lvl;
}

void Hero::setBaseHP(int h){
    baseHP = h;
}

void Hero::setStyrke(int s){
    styrke=s;
}



void Hero::chooseNameByCode(string name){
    navn = name;
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
    if(isWeaponEquipped()){ //if weapon is equipped, the bonus dmg is added accordingly
        currentWeapon->use();
        if(currentWeapon->getHoldbarhed() ==0){
            cout << "Weapon is broken !!! Please pick a new weapon to enhance fighting capeabilities!!!" << endl;
            sleep(1);
        }
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

void Hero::addToHeroKillList(string enemyName){
    heroKillList.push_back(enemyName);
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

int Hero::getBaseHp() const{
    return baseHP;
}

int Hero::getGold() const{
    return gold;
}

void Hero::getStats(){
    if(isWeaponEquipped()){
        cout << "\n ---- Hero stats with weapon ----" << endl; //to visualize what weapon does to strength.
            cout << "Weapon equipped: " << currentWeapon->getName() << endl;
            cout << "Name: " << getName() << endl;
            cout << "XP: " << getXP() << endl;
            cout << "Level: " << getLevel() << endl;
            cout << "Styrke: " << getStyrke()<< endl;
            cout << "Styrke with weapon: " << getStyrke()*(1+currentWeapon->getStyrkeModifier()) + currentWeapon->getSkade() << endl;
            cout << "HP: " << getHP() << endl;
            cout << "Gold: " << getGold() << endl;
    }
    else{
        cout << "\n ---- Hero stats ----" << endl;
        cout << "Name: " << getName() << endl;
        cout << "XP: " << getXP() << endl;
        cout << "Level: " << getLevel() << endl;
        cout << "Styrke: " << getStyrke() << endl;
        cout << "HP: " << getHP() << endl;
        cout << "Gold: " << getGold() << endl;
    }
    
    if(weapons.size()!=0){
        cout << "\n -----Weapons-----" << endl;
        showWeapons();
    } 
}

void Hero::setHP(int h){
    hp = h;
}

void Hero::getNewWeapon(Weapon newWeapon){
    weapons.push_back(newWeapon);
}

void Hero::equipWeapon(const string weaponName){
    for(Weapon& w : weapons){
        if(w.getName() == weaponName){
            currentWeapon = &w;
            cout << "Weapon equipped: " << weaponName << endl;
            return;
        }
    }
    cout << "Weapon couldnt be found" << endl;
}

bool Hero::isWeaponEquipped(){
    
    if(currentWeapon == nullptr){
        return false;
    }
    return currentWeapon->hasHolbarhed();
}

void Hero::showWeapons() const{
    for(Weapon w : weapons){
        if(w.hasHolbarhed()){
            cout << "Weapon: " << w.getName() << endl;
        }
    }
}

bool Hero::hasWeapon() const{
    return weapons.size()!=0;
}

vector<Weapon> Hero::getWeapons() const{
    return weapons;
}

void Hero::showWeaponStats() const { //function for showing weapon stats
    cout << "Showing weapon stats: " << endl;
    if(weapons.size()>0){
        for(Weapon w : weapons){
            cout << "\n";
            cout << "Weapon: " << w.getName() << endl;
            cout << "Skade: " << w.getSkade() << endl;
            cout << "SkadeModifier: " << w.getStyrkeModifier() << endl;
            cout << "Holdbarhed: " << w.getHoldbarhed() << endl; 
            cout << "number of enemies slain: " << w.getKillList().size();
            cout << "\n";
            sleep(2);
        }
    }
    else{
        cout << getName() << " has no weapons yet" << endl;
    }
    
}

void Hero::addKillToKillList(string enemyName){
    if(isWeaponEquipped()){
        if(currentWeapon == nullptr){
            cout << "Error: currentweapon is null!" << endl;
            return;
        }
        cout << "Adding to weapon kill list: " << enemyName << endl;
        currentWeapon->addToKillList(enemyName);
    }
    cout << "Adding to hero kill list: " << enemyName << endl;
    heroKillList.push_back(enemyName);
}

vector <string> Hero::getHeroKillList() const {
    return heroKillList;
}

bool Hero::erDoed(){
    return hp<0;
}

Hero::~Hero(){}