#include "Grotte.h"
#include "MainCharacter.h"

Grotte::Grotte(){}

// Constructs a grotte based on the hero's attributes and a difficulty modifier cavelevel.
// The modifier increases the strength of enemies and the amount of gold in the grotte.
Grotte::Grotte(const Hero& hero, float caveLevel){
    int heroStrength = hero.getStyrke();
    int heroHP = hero.getHP();
    int StrenghtAndHP = heroStrength * heroHP;
    enemies = factory.createEnemyList(heroStrength*(1+caveLevel/10), heroHP*(1+caveLevel/10));
    grotteName = "Grotte LVL " + to_string(int(caveLevel));
    grotteLevel = int(caveLevel);
    grotteGold = 50*caveLevel;
}

// Returns a reference to the list of enemies in the grotte.
// This function is used to access and modify the enemies during a fight.
vector <Enemy*>& Grotte::getEnemyList(){
    return enemies;
}

void Grotte::showEnemies() const{
    int numberOfEnemies = 0;
    for(Enemy* enemy : enemies){
        cout << enemy->getName() << endl;
        numberOfEnemies ++;
    }
}

void Grotte::showGrotteName() const{
    cout << grotteName << " ";
}

int Grotte::getGrotteGold() const{
    return grotteGold;
}

int Grotte::getGrotteLevel() const{
    return grotteLevel;
}

bool Grotte::grottePopulated() const{
    return (enemies.size()>0);
}

Grotte::~Grotte(){
    //cleanup
    for(Enemy* enemy : enemies){
        delete enemy;
    }
}