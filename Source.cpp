#include "Enemy.h"
#include "Enemies.h"
#include "MainCharacter.h"
#include "Grotte.h"
using namespace std;
#include <string>
#include <iostream>
#include <unistd.h>

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

void fight(Hero* hero, Enemy* enemy){
    bool validfight = true;
    while(validfight){
        cout << hero->getName() << " angriber " << enemy->getName() << endl;
            enemy->tagSkade(hero->getStyrke());
            if(enemy->erDoed()){
                cout << hero->getName() << " vandt!!" << endl;
                hero->gainXP(enemy->getXP());
                enemy->setHP();
                validfight = false;
            }
            cout << enemy->getName() << " angriber!!" <<endl;
            hero->takeDamage(enemy->angrib());
            if(hero->erDoed()){
                cout << hero->getName() << " døde. Bedre held næste gang" << endl;
                validfight = false;
            }
    }
}



int main(){

    cout << "Starting game ..." << endl;
    Hero hero;
    startGame(hero);

    while(true){
        Grotte grotte(hero);
        cout << "\n--- Main Menu ---" << endl;
        cout << "1. Show Hero Stats" << endl;
        cout << "2. Show Grotter" << endl;
        cout << "3. Choose grotte" << endl;
        cout << "4. Exit Game" << endl; 

        int choice;
        cin >> choice;
        usleep(100);
        if (choice ==1){
            hero.getStats();
        }
        if(choice == 2){
            grotte.showEnemies();
        }
        
        if(choice ==3){
            int grotteChoice;
            cout << "Showing grotter" << endl;
            grotte.showGrotteName();
            cout << "Choose grotte: 1, 2 or 3!!" << endl;
            cin >> grotteChoice;
            if(grotteChoice == 1){
                string chosenEnemy;
                vector <Enemy*> currenctEnemies = grotte.getEnemyList();
                cout << "Showing enemies in grotte" << endl;
                grotte.showEnemies();
                cout << "Choose an enemy" << endl;
                cin >> chosenEnemy;
                for(Enemy* enemy : currenctEnemies){
                    if(chosenEnemy == enemy->getName()){
                        fight(&hero, enemy);
                    }
                }

            }
            
        }
        // if(choice == 6){
        //     cout << "Choose an enemy: " << endl;
        //     enemies.printNames();
        //     string chosenEnemy;
        //     cin >> chosenEnemy;
        //     if(chosenEnemy == "cheatcode"){
        //         hero.setHP(10000);
        //         hero.setStyrke(1000);
        //         continue;
        //     }
        //     Enemy* currentEnemy = enemies.getEnemy(chosenEnemy);
        //     bool validEnemy = true;
        //     if (currentEnemy == nullptr) {
        //         cout << "Enemy not found! Please try again." << endl;
        //         validEnemy = false;
    
        //         // Clear cin state and ignore invalid input
        //         cin.clear();
        //         continue; // Prompt the user again
        //     }
        //     while(validEnemy){
        //         cout << hero.getName() << " angriber " << currentEnemy->getName() << endl;
        //         currentEnemy->tagSkade(hero.getStyrke());
        //         if(currentEnemy->erDoed()){
        //             cout << hero.getName() << " vandt!!" << endl;
        //             hero.gainXP(currentEnemy->getXP());
        //             currentEnemy->setHP();
        //             break;
        //         }
        //         cout << currentEnemy->getName() << " angriber!!" <<endl;
        //         hero.takeDamage(currentEnemy->angrib());
        //         if(hero.erDoed()){
        //             cout << hero.getName() << " døde. Bedre held næste gang" << endl;
        //             return 0;
        //         }
        //     }
            
            
        // }
        if(choice == 4){
            cout << "Exiting game..." << endl;
            return 0;
        }
        if(choice != 1 && choice != 2 && choice != 3 && choice != 4){

            cout << "Invalid input: " << choice <<  " try again!!" << endl;
        }
        sleep(1);

    }


    return 0;
}