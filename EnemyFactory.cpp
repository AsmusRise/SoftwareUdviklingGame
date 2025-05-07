#include "EnemyFactory.h"


EnemyFactory::EnemyFactory(){
    modifierNames = {"veryweak","weak","normal","strong","stronger","strongest","godlike"};
    enemyNames = {"Horse","Goblin", "Ape", "Snake", "Unicorn", "Dragon"};
}

Enemy* EnemyFactory::createEnemy(string name, int modifier){
    //check for valid m
    int validCalls =  modifierNames.size();
    if(modifier>validCalls || modifier<0){
        cout << "no valid modifier argument" << endl;
        return nullptr;
    }

    //creating the object according to name.
    if(name == "Hest") {
        return new Hest(modifier);
    }
    else if(name == "Goblin"){
        return new Goblin(modifier);
    }
    else if(name == "Snake"){
        return new Snake(modifier);
    }
    else if(name == "Ape"){
        return new Ape(modifier);
    }
    else if(name == "Dragon"){
        return new Dragon(modifier);
    }
    else if(name == "Unicorn"){
        return new Unicorn(modifier);
    }
    else{
        cout << "invalid enemy name argument" << endl;
        return nullptr;
    }
}

vector<Enemy*> EnemyFactory::createEnemyList(int heroAttack, int heroHP){
    vector <Enemy*> enemyList;
    for(string name : enemyNames){
        for(int i = 0; i<enemyNames.size(); i++){
            Enemy* enemy = createEnemy(name, i);
            if(enemy && enemy->getStyrke()<heroAttack && enemy->getHP()<heroHP){
                enemyList.push_back(enemy);
            }
            else{
                delete enemy;
            }
        }
    }
    return enemyList;
}

EnemyFactory::~EnemyFactory(){}
