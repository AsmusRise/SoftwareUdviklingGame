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
}

void Hero::createHero(string n){
    navn = n;
}

void Hero::setName(){
    cout << "Choose a name: " << endl;
    cin >> navn;
}

void Hero::chooseHero(){
    while(true){
        cout << "Showing heroes: " << endl;
        showHeroes();
        string chooseName;
        cout << "Choose hero: " << endl;
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
    return styrke;
}

void Hero::takeDamage(int d){
    hp -=d;
}

void Hero::levelUp(){
    level++;
    baseHP +=2;
    hp = baseHP;
    styrke += 1;
}

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

void Hero::setStyrke(int s){
    styrke = s;
}

bool Hero::erDoed(){
    return hp<0;
}

Hero::~Hero(){}