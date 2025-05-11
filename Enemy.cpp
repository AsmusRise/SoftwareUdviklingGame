#include "Enemy.h"

Enemy::Enemy(){
    modifierNames = {"veryweak","weak","normal","strong","stronger","strongest","godlike"};
}


string Enemy::getName(){
    return navn;
}

float Enemy::angrib(){
    return styrke;
}

void Enemy::tagSkade(float s){
    hp -= s;
}

float Enemy::getXP(){
    return xp;
}

bool Enemy::erDoed(){
    return hp<0;
}

float Enemy::getStyrke(){
    return styrke*1.0;
}

float Enemy::getHP(){
    return hp;
}

// Calculates a new modifier value based on the input.
// The modifier increases linearly with the input, starting at 0.5.
float Enemy::newModifier(float modifier){
    float newModifier = 0.5+(modifier/5);
    return newModifier;
}

Enemy::~Enemy(){}
