#include "Enemy.h"
#include "Enemies.h"
#include "MainCharacter.h"
#include "Grotte.h"
using namespace std;
#include <string>
#include <iostream>
#include <unistd.h>
#include <memory>

void startGame(Hero& hero){ //function to initialize hero by create or choosing.
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
    //function to fight between hero and enemy
    //validfight checks if the fight is ongoing.
    bool validfight = true;
    while(validfight){
        cout << hero->getName() << " angriber " << enemy->getName() << endl;
            enemy->tagSkade(hero->getStyrke());
            if(enemy->erDoed()){
                //hero gets xp, and hp is reset (hero heals back up)
                cout << hero->getName() << " vandt!!" << endl;
                hero->gainXP(enemy->getXP());
                enemy->setHP();
                validfight = false;
                break;
            }
            cout << enemy->getName() << " angriber!!" <<endl;
            hero->takeDamage(enemy->angrib());

            //checks if hero is dead
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
    int heroCurrentLVL = 0;
    vector<unique_ptr<Grotte>> grotter;

    while(true){
        if(heroCurrentLVL != hero.getLevel()){
            
            if(heroCurrentLVL!=0){
                grotter.clear();
            }
            for(int i=1; i<4; i++){
                grotter.push_back(make_unique<Grotte>(hero,i));
            }
            heroCurrentLVL = hero.getLevel();
        }
        
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
        else if(choice == 2){
            for(const auto& grottePtr : grotter){
                const Grotte& grotte = *grottePtr;
                grotte.showGrotteName();
            }
        }
        
        else if(choice ==3){
            int grotteChoice=0;
            cout << "Showing grotter" << endl;
            for(const auto& grottePtr : grotter){
                const Grotte& grotte = *grottePtr;
                grotte.showGrotteName();
                cout << "\n";
            }
            while(1>grotteChoice || grotteChoice>3){
                cout << "Choose grotte: 1, 2 or 3!!" << endl;
                cin >> grotteChoice;
            }
            string chosenEnemy;
            vector <Enemy*>& currenctEnemies = grotter[grotteChoice-1]->getEnemyList();
            while(grotter[grotteChoice-1]->grottePopulated()){
                cout << "Showing enemies in ";
                grotter[grotteChoice -1]->showGrotteName();
                cout << endl;

                grotter[grotteChoice-1]->showEnemies();
                cout << "Choose an enemy" << endl;
                cin >> chosenEnemy;
                for(Enemy* enemy : currenctEnemies){
                    if(chosenEnemy == enemy->getName()){
                        fight(&hero, enemy);
                        if(hero.erDoed()){
                            return 0;
                        }
                        auto it = find(currenctEnemies.begin(), currenctEnemies.end(), enemy);
                        if (it != currenctEnemies.end()) {
                            cout << "deleting enemy" << enemy->getName() << endl;
                            currenctEnemies.erase(it);
                            delete enemy;
                            
                        } else {
                            cout << "Enemy not found in the list!" << endl;
                        }
                        break;
                    }

                }

            }
            cout << "All enemies in ";
            grotter[grotteChoice-1]->showGrotteName();
            cout << " have been defeated!!" << endl;
            hero.gainGold(grotter[grotteChoice-1]->getGrotteGold());
            
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
        else if(choice == 4){
            cout << "Exiting game..." << endl;
            return 0;
        }
        else if(choice != 1 && choice != 2 && choice != 3 && choice != 4){

            cout << "Invalid input: " << choice <<  " try again!!" << endl;
        }
        sleep(1);

    }


    return 0;
}