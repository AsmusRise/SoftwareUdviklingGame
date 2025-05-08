#include "Enemy.h"

Enemy::Enemy(){
    modifierNames = {"veryweak","weak","normal","strong","stronger","strongest","godlike"};
}


string Enemy::getName(){
    return navn;
}

int Enemy::angrib(){
    return styrke;
}

void Enemy::tagSkade(int s){
    hp -= s;
}

void Enemy::setHP(){
    hp = basisHP;
}

int Enemy::getXP(){
    return xp;
}

bool Enemy::erDoed(){
    return hp<0;
}

int Enemy::getStyrke(){
    return styrke*1.0;
}

int Enemy::getHP(){
    return hp;
}

float Enemy::newModifier(int modifier){
    float newModifier = (1 + modifier / 10.0);
    return newModifier;
}

Enemy::~Enemy(){}
