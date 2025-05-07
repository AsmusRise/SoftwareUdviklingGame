#include "EnemyFactory.h"


EnemyFactory::EnemyFactory(){
    modifierNames = {"veryweak","weak","normal","strong","stronger","strongest","godlike"};
    enemyNames = {"Horse","Goblin", "Ape", "Snake", "Unicorn", "Dragon"};
}

Enemy* EnemyFactory::createEnemy(string n, int m){
    //check for valid m
    int validCalls =  modifierNames.size();
    if(m>validCalls || m<0){
        cout << "no valid modifier argument" << endl;
        return nullptr;
    }
    if(find(enemyNames.begin(), enemyNames.end(), n) == enemyNames.end()){
        cout << "no valid enemy name argument" << endl;
        return nullptr;
    }

    string modifierName;
    modifierName = modifierNames[m];

    return new Enemy(n,m);

}

EnemyFactory::~EnemyFactory(){}
