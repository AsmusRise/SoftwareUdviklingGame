#include "Grotte.h"
#include "MainCharacter.h"

Grotte::Grotte(){}

// Constructs a grotte based on the hero's attributes and a difficulty modifier.
// The modifier increases the strength of enemies and the amount of gold in the grotte.
Grotte::Grotte(const Hero& hero, float caveModifier){
    cout << "Grotte constructor called" << endl;
    int heroStrength = hero.getStyrke();
    int heroHP = hero.getHP();
    int StrenghtAndHP = heroStrength * heroHP;
    enemies = factory.createEnemyList(heroStrength*(1+caveModifier/10), heroHP*(1+caveModifier/10));
    grotteName = "Grotte LVL " + to_string(hero.getLevel()-1+int(caveModifier));
    grotteGold = 50*caveModifier;
}

// Returns a reference to the list of enemies in the grotte.
// This function is used to access and modify the enemies during a fight.
vector <Enemy*>& Grotte::getEnemyList(){
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
    cout << grotteName << " ";
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