#include "EnemyFactory.h"


EnemyFactory::EnemyFactory(){ //list of 
    modifierNames = {"veryweak","weak","normal","strong","stronger","strongest","godlike"};
    enemyNames = {"Hest","Goblin", "Ape", "Snake", "Unicorn", "Dragon"};
}

// Creates an enemy of the specified type and difficulty modifier.
// The modifier must be between 1 and the size of `modifierNames`.
Enemy* EnemyFactory::createEnemy(string name, int modifier){
    //check for valid m
    int validCalls =  modifierNames.size();
    if(modifier>validCalls || modifier<0){
        cout << "no valid modifier argument" << endl;
        return nullptr;
    }
    if(name.empty()){
        cout << "Invalid enemy name: name empty" << endl;
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

//creating list of enemies which will populate cave
vector<Enemy*> EnemyFactory::createEnemyList(float heroAttack, float heroHP){
    vector <Enemy*> enemyList;
    for(string name : enemyNames){
        for(int modifier = 1; modifier<enemyNames.size()+1; modifier++){
            Enemy* enemy = createEnemy(name, modifier);
            if(enemy){
                //checks if enemy hp*strength is bigger than hp*strength of hero
                //also checks if enemy/hero > 0.6 to make sure enemy is not too weak.
                //cout << "the division: " << (enemy->getStyrke()*enemy->getHP())*1.0/(heroAttack*heroHP) << endl;
                if(enemy && enemy->getStyrke()*enemy->getHP()<heroAttack*heroHP && (enemy->getStyrke()*enemy->getHP())*1.0/(heroAttack*heroHP) >0.2 ){
                    enemyList.push_back(enemy);
                   }
                else{
                    delete enemy;
                }
            }
        }
    }
    return enemyList;
}

EnemyFactory::~EnemyFactory(){}
