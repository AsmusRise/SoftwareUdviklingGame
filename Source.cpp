#include "Enemy.h"
#include "Enemies.h"
#include "MainCharacter.h"
using namespace std;
#include <string>
#include <iostream>

void startGame(){
    Hero h;
    string valg;
    while(true){
        cout << "Vil du lave eller vælge en eksisterende hero? (type [choose] or [create])" << endl;
        cin >> valg;
        if(valg =="choose"){
            h.chooseHero();
            return;
        }
        else if(valg == "create"){
            h.setName();
            return;
        }
        cout <<"invalid option, please try again! " << endl;
    }
}


Enemies createEnemies(){
    vector<Enemy*> enemies;
    vector<string> enemiesNames = {"Hest", "Weak Golbin", "Strong Goblin", "Stronger Goblin","The Strongest Goblin","Abe King", "Unicorn", "Dragon"};
    for(int i=0; i<enemiesNames.size(); i++){
        enemies.push_back(new Enemy(enemiesNames[i]));
    }
    cout << "Enemies created: " << endl;
    for(int i =0; i<enemiesNames.size(); i++){
        cout << enemies[i]->getName() << endl;
    }
    Enemies enemies(enemies);
    return enemies;
}

void showEnemies(vector<Enemy> enemies){
    
    for(int i=0; i<enemies.size();i++){
    }
}

int main(){
    Enemies enemies = createEnemies();
    cout << "Starting game ..." << endl;
    startGame();

    return 0;
}