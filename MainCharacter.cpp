#include "MainCharacter.h"

Hero::Hero(){}

void Hero::createHero(string n){
    navn = n;
    xp = 0;
    level = 1;
    styrke = 2;
    hp = 10;
}

void Hero::loadHero(){
    xp = 0;
    level = 1;
    styrke =2;
    hp =10;
}

void Hero::chooseHero(string n){
    for(int i = 0; i < heroes.size(); i++) {
        if (heroes[i] == n) {
            navn = n;
            loadHero();
            return;
        }
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