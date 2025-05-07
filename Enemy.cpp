#include "Enemy.h"

Enemy::Enemy(){}

Enemy::Enemy(string n, int m){
    navn = n;
    if(navn == "Hest"){
        basisHP =4*(1+m/10);
        hp = 4*(1+m/10);
        styrke = 1*(1+m/10);
        xp = 100*(1+m/10);
    }
    else if(navn == "Goblin"){
        basisHP =4*(1+m/10);
        hp = 4*(1+m/10);
        styrke = 2*(1+m/10);
        xp = 200*(1+m/10);
    }
    else if(navn == "Ape"){
        basisHP =30*(1+m/10);
        hp = 30*(1+m/10);
        styrke = 5*(1+m/10);
        xp = 1000*(1+m/10);
    }
    else if (navn == "Snake"){
        basisHP = 10;
        hp = 10;
        styrke = 3;
        xp = 400;
    }
    else if(navn == "Unicorn"){
        basisHP =5*(1+m/10);
        hp = 5*(1+m/10);
        styrke = 8*(1+m/10);
        xp = 1500*(1+m/10);
    }
    else if(navn == "Dragon"){
        basisHP =100*(1+m/10);
        hp = 100*(1+m/10);
        styrke = 10*(1+m/10);
        xp = 3000*(1+m/10);
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
