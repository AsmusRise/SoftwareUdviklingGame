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
    return styrke;
}

int Enemy::getHP(){
    return hp;
}

Enemy::~Enemy(){}
