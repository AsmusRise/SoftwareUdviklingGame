#include "Enemy.h"

Enemy::Enemy(){}

Enemy::Enemy(string n){
    navn = n;
    if(navn == "Hest"){
        basisHP =4;
        hp = 4;
        styrke = 1;
        xp = 100;
    }
    else if(navn == "WeakGoblin"){
        basisHP =4;
        hp = 4;
        styrke = 2;
        xp = 200;
    }
    else if(navn == "StrongGoblin"){
        basisHP =8;
        hp = 8;
        styrke = 3;
        xp = 400;
    }
    else if(navn == "StrongerGoblin"){
        basisHP =10;
        hp = 10;
        styrke = 4;
        xp = 500;
    }
    else if(navn == "TheStrongestGoblin"){
        basisHP =15;
        hp = 15;
        styrke = 5;
        xp = 800;
    }
    else if(navn == "AbeKing"){
        basisHP =30;
        hp = 30;
        styrke = 5;
        xp = 1000;
    }
    else if(navn == "Unicorn"){
        basisHP =5;
        hp = 5;
        styrke = 8;
        xp = 1500;
    }
    else if(navn == "Dragon"){
        basisHP =100;
        hp = 100;
        styrke = 10;
        xp = 3000;
    }
    else{
        hp = 0;
        styrke = 0;
        xp = 0; 
        navn = "invalid";
        cout << "invalid name:" << endl;
    }

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
