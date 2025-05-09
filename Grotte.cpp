#include "Grotte.h"
#include "MainCharacter.h"

Grotte::Grotte(){}

Grotte::Grotte(const Hero& hero, float caveModifier){
    cout << "Grotte constructor called" << endl;
    int heroStrength = hero.getStyrke();
    int heroHP = hero.getHP();
    int StrenghtAndHP = heroStrength * heroHP;
    enemies = factory.createEnemyList(heroStrength*(1+caveModifier/10), heroHP*(1+caveModifier/10));
    grotteName = "Grotte LVL " + to_string(hero.getLevel()-1+caveModifier);
    grotteGold = 50*caveModifier;
}

vector <Enemy*>& Grotte::getEnemyList(){ //why am i having this?
    return enemies;
}

void Grotte::showEnemies() const{
    cout << "in showEnemies function " << endl;
    int numberOfEnemies = 0;
    for(Enemy* enemy : enemies){
        //cout << "show enemies For loop" << endl;
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

bool Grotte::grottePopulated() const{
    return (enemies.size()>0);
}

Grotte::~Grotte(){
    //cleanup
    cout << "deleting enemies" << endl;
    for(Enemy* enemy : enemies){
        delete enemy;
    }
}