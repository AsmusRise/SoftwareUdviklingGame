#include "MainCharacter.h"

Hero::Hero(){}

void Hero::createHero(string n){
    navn = n;
    xp = 0;
    level = 0;
    styrke = 2;
}

void Hero::loadHero(string n){
    for(int i = 0; i < heroes.size(); i++) {
        if (heroes[i] == n) {
            navn = n;
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

Hero::~Hero(){}