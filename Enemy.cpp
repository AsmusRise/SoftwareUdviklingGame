#include "Enemy.h"

Enemy::Enemy(){}

Enemy::Enemy(string n){
    navn = n;
    if(navn == "Hest"){
        hp = 4;
        styrke = 1;
        xp = 100;
    }
    else if(navn == "Weak Goblin"){
        hp = 4;
        styrke = 2;
        xp = 200;
    }
    else if(navn == "Strong Goblin"){
        hp = 8;
        styrke = 3;
        xp = 400;
    }
    else if(navn == "Stronger Goblin"){
        hp = 10;
        styrke = 4;
        xp = 500;
    }
    else if(navn == "The Strongest Goblin"){
        hp = 15;
        styrke = 5;
        xp = 800;
    }
    else if(navn == "Abe King"){
        hp = 30;
        styrke = 5;
        xp = 1000;
    }
    else if(navn == "Unicorn"){
        hp = 5;
        styrke = 8;
        xp = 1500;
    }
    else if(navn == "Dragon"){
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

int Enemy::getXP(){
    return xp;
}

bool Enemy::erDoed(){
    return hp<0;
}

Enemy::~Enemy(){}
