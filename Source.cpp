#include "Enemy.h"
#include "Enemies.h"
#include "MainCharacter.h"
using namespace std;
#include <string>
#include <iostream>

void startGame(Hero& hero){
    string valg;
    while(true){
        cout << "Vil du lave eller vælge en eksisterende hero? (type [choose] or [create])" << endl;
        cin >> valg;
        if(valg =="choose"){
            hero.chooseHero();
            return;
        }
        else if(valg == "create"){
            hero.setName();
            return;
        }
        cout <<"invalid option, please try again! " << endl;
    }
}


Enemies createEnemies(){
    vector<Enemy*> enemyList;
    vector<string> enemiesNames = {"Hest", "Weak Goblin", "Strong Goblin", "Stronger Goblin","The Strongest Goblin","Abe King", "Unicorn", "Dragon"};
    for(int i=0; i<enemiesNames.size(); i++){
        enemyList.push_back(new Enemy(enemiesNames[i]));
    }
    cout << "Enemies created: " << endl;
    for(int i =0; i<enemiesNames.size(); i++){
        cout << enemyList[i]->getName() << endl;
    }
    Enemies enemies(enemyList);
    return enemies;
}

void showEnemies(vector<Enemy> enemies){
    
    for(int i=0; i<enemies.size();i++){
    }
}

int main(){
    Enemies enemies = createEnemies();
    cout << "Starting game ..." << endl;
    Hero hero;
    startGame(hero);

    while(true){
        cout << "\n--- Main Menu ---" << endl;
        cout << "1. Show Hero Stats" << endl;
        cout << "2. Show Enemies" << endl;
        cout << "3. Attack an Enemy" << endl;
        cout << "4. Exit Game" << endl; 

        int choice;
        cin >> choice;
        if (choice ==1){
            hero.getStats();
        }
        if(choice == 2){
            enemies.printNames();
        }
        if(choice == 3){
            cout << "Choose an enemy: " << endl;
            enemies.printNames();
            string chosenEnemy;
            cin >> chosenEnemy;
            Enemy* currentEnemy = enemies.getEnemy(chosenEnemy);
            while(true){
                cout << hero.getName() << " angriber " << currentEnemy->getName() << endl;
                currentEnemy->tagSkade(hero.getStyrke());
                if(currentEnemy->erDoed()){
                    cout << hero.getName() << " vandt!!" << endl;
                    break;
                }
                cout << currentEnemy->getName() << " angriber!!" <<endl;
                hero.takeDamage(currentEnemy->angrib());
                if(hero.erDoed()){
                    cout << hero.getName() << " døde. Bedre held næste gang" << endl;
                    return 0;
                }
            }
            hero.gainXP(currentEnemy->getXP());
            
        }
        if(choice == 4){
            cout << "Exiting game..." << endl;
            return 0;
        }

    }


    return 0;
}