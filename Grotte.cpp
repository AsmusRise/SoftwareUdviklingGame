#include "Grotte.h"
#include "MainCharacter.h"

Grotte::Grotte(){}

Grotte::Grotte(const Hero& hero){
    cout << "Grotte constructor called" << endl;
    int heroStrength = hero.getStyrke();
    int heroHP = hero.getHP();
    int StrenghtAndHP = heroStrength * heroHP;
    enemies = factory.createEnemyList(heroStrength, heroHP);
    grotteName = "Grotte LVL " + to_string(hero.getLevel());
    grotteGold = hero.getLevel() * 50;
}

vector <Enemy*> Grotte::getEnemyList(){ //why am i having this?
    return enemies;
}

void Grotte::showEnemies() const{
    cout << "in showEnemies function " << endl;
    int numberOfEnemies = 0;
    for(Enemy* enemy : enemies){
        cout << "show enemies For loop" << endl;
        cout << enemy->getName() << endl;
        numberOfEnemies ++;
    }
    cout << "Number of enemies: " << numberOfEnemies << endl;
}

void Grotte::showGrotteName() const{
    cout << grotteName << endl;
}

int Grotte::getGrotteGold() const{
    return grotteGold;
}

Grotte::~Grotte(){
    //cleanup
    for(Enemy* enemy : enemies){
        delete enemy;
        cout << "deleting enemies" << endl;
    }
}