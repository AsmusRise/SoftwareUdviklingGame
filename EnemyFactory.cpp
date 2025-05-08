#include "EnemyFactory.h"


EnemyFactory::EnemyFactory(){
    modifierNames = {"veryweak","weak","normal","strong","stronger","strongest","godlike"};
    enemyNames = {"Hest","Goblin", "Ape", "Snake", "Unicorn", "Dragon"};
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
        cout << "Creating Hest with modifier: " << modifier << endl;
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
    cout << "Creating enemies with factory: size of enemynameslist is: " << enemyNames.size() << endl;
    for(string name : enemyNames){
        cout << "trying to create enemy: " << name << endl;
        for(int modifier = 1; modifier<enemyNames.size()+1; modifier++){
            Enemy* enemy = createEnemy(name, modifier);
            //checks if enemy hp*strength is bigger than hp*strength of hero
            //also checks if enemy/hero > 0.6 to make sure enemy is not too weak.
            //cout << "the division: " << (enemy->getStyrke()*enemy->getHP())*1.0/(heroAttack*heroHP) << endl;
            if(enemy && enemy->getStyrke()*enemy->getHP()<heroAttack*heroHP){
                enemyList.push_back(enemy);
                cout << "made an enemy succesfully: " << enemy->getName() << endl;
                cout << "The division: " << (enemy->getStyrke()*enemy->getHP())*1.0/(heroAttack*heroHP) << endl;
                cout << "styrke, HP, xp" << enemy->getStyrke()*1.0 << enemy->getHP() << enemy->getXP() << endl;
            }
            else{
                delete enemy;
            }
        }
    }
    return enemyList;
}

EnemyFactory::~EnemyFactory(){}
