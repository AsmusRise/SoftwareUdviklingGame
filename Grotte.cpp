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
    if(int(caveLevel) == 1){ //manuelt tilføjer våben i de første 5 caves, da generation ikke var krav
        weaponInCave = Weapon("pind",0,1,10);
        cout << "grotte 1 created with weapon" << endl;
    }
    if(int(caveLevel) == 2){
        weaponInCave = Weapon("Metalroer",5,2,20);
        cout << "grotte 2 created with weapon" << endl;
    }
    if(int(caveLevel) == 3){
        weaponInCave = Weapon("Kniv",10,2,40);
        cout << "grotte 3 created with weapon" << endl;
    }
    if(int(caveLevel) == 4){
        weaponInCave = Weapon("Svaerd",20,2,60);
    }
    if(int(caveLevel) == 5){
        weaponInCave = Weapon("Morgenstjerne",30,3,100);
    }
}

// Returns a reference to the list of enemies in the grotte.
// This function is used to access and modify the enemies during a fight.
vector <Enemy*>& Grotte::getEnemyList(){
    return enemies;
}

void Grotte::showEnemies() const{
    int numberOfEnemies = 0;
    int enemyIndex = 1;
    for(Enemy* enemy : enemies){
        cout << enemyIndex << ": "<< enemy->getName() << endl;
        numberOfEnemies ++;
        enemyIndex++;
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

bool Grotte::isWeaponInGrotte() const{
    return !weaponInCave.getName().empty();
}

Weapon Grotte::getWeapon(){
    return weaponInCave;
}

Grotte::~Grotte(){
    //cleanup
    for(Enemy* enemy : enemies){
        delete enemy;
    }
}