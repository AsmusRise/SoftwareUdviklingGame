#include "Enemies.h"

Enemies::Enemies(){}

Enemies::Enemies(vector<Enemy*> e){
    enemies = e;
}

void Enemies::printNames(){
    for(int i =0; i<enemies.size();i++){
        cout << enemies[i]->getName() << endl;
    }
    cout << "- - - - - - " << endl;
}

void Enemies::addEnemy(Enemy* e) {
    enemies.push_back(e); // Add the Enemy pointer to the vector
}

Enemy* Enemies::getEnemy(string n){
    for(int i= 0; i<enemies.size(); i++){
        if(enemies[i]->getName() == n){
            return enemies[i];
        }
    }
    return nullptr;
}

Enemies::~Enemies(){}