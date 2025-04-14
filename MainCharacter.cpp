#include "MainCharacter.h"

Hero::Hero(){}

Hero::Hero(){
    initializeHeroes();
    navn = "empty";
    xp = 0;
    level = 1;
    styrke = 2;
    hp = 10;
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

void Hero::levelUp(){
    level++;
}

void Hero::gainXP(int XP){
    xp += XP;
    if(xp>level*1000){
        xp =xp-level*1000;
        levelUp();
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

Hero::~Hero(){}