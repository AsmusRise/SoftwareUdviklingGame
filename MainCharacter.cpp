#include "MainCharacter.h"

Hero::Hero(){
    initializeHeroes();
    navn = "empty";
    xp = 0;
    level = 1;
    styrke = 2;
    hp = 10;
    baseHP=10;
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
    }
}

void Hero::initializeHeroes(){
    heroes = {"August", "Goatie", "Goldielock", "Kaj", "Alfredo"};
}

void Hero::showHeroes(){
    for(int i =0; i<heroes.size(); i++){
        cout << heroes[i] << endl;
    }
}

string Hero::getName(){
    return navn;
}

int Hero::getXP(){
    return xp;
}

int Hero::getLevel(){
    return level;
}

int Hero::getStyrke(){
    return styrke;
}

int Hero::getHP(){
    return hp;
}

void Hero::getStats(){
    cout << "\n ---- Hero stats ----" << endl;
            cout << "Name: " << getName() << endl;
            cout << "XP: " << getXP() << endl;
            cout << "Level: " << getLevel() << endl;
            cout << "Styrke: " << getStyrke() << endl;
            cout << "HP: " << getHP() << endl;
}

bool Hero::erDoed(){
    return hp<0;
}

Hero::~Hero(){}