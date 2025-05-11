#include "Enemy.h"
#include "Enemies.h"
#include "MainCharacter.h"
#include "Grotte.h"
using namespace std;
#include <string>
#include <iostream>
#include <unistd.h>
#include <memory>

void makeNewCave(Hero& hero, vector<unique_ptr<Grotte>>& grotter);

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
        // The `validfight` variable ensures the fight continues until either the hero or the enemy is defeated.
    bool validfight = true;
    while(validfight){
        cout << hero->getName() << " angriber " << enemy->getName() << endl;
            enemy->tagSkade(hero->getStyrke());
            if(enemy->erDoed()){
                //hero gets xp, and hp is reset (hero heals back up)
                cout << hero->getName() << " vandt!!" << endl;
                hero->gainXP(enemy->getXP());
                validfight = false;
                break;
            }
            cout << enemy->getName() << " angriber!!" <<endl;
            hero->takeDamage(enemy->angrib());

            //checks if hero is dead
            if(hero->erDoed()){ //checks if hero is dead after attack
                cout << hero->getName() << " døde. Bedre held næste gang" << endl;
                validfight = false;
            }
    }
}

// Function: fightInGrotte
// Purpose: Allows the hero to fight through a selected grotte, defeating enemies one by one.
// Parameters:
//   - hero: The hero object (passed by reference) whose stats will be updated during the fight.
//   - grotter: A vector of unique pointers to grotter, representing the available caves.
// Behavior:
//   - Prompts the user to select a grotte.
//   - Handles the fight logic for each enemy in the grotte.
//   - Removes the grotte from the list once all enemies are defeated.
void fightInGrotte(Hero& hero, vector<unique_ptr<Grotte>>& grotter){
    int heroLevelAtStart = hero.getLevel();
    //while loop for choosing a valid grotte
    int grotteChoice=0;
    while(grotteChoice <= 0 || grotteChoice > grotter.size() || grotter[grotteChoice - 1] == nullptr){
        cout << "Choose a valid grotte: " << endl;
        for(int i = 0; i < grotter.size(); i++){
            grotter[i]->showGrotteName();
            cout << "\n";      
        }
        cin >> grotteChoice;
    }
    int grotteChoiceIndex = grotteChoice-1; 

    //choosing an enemy in the grotte
    string chosenEnemy;
    vector <Enemy*>& currenctEnemies = grotter[grotteChoiceIndex]->getEnemyList();
    while(grotter[grotteChoiceIndex]->grottePopulated()){ //checks if enemies alive are in cave
        cout << "Showing enemies in ";
        grotter[grotteChoiceIndex]->showGrotteName();
        cout << endl;

        grotter[grotteChoiceIndex]->showEnemies();
        cout << endl;
        cout << "Choose an enemy" << endl;
        cin >> chosenEnemy;

        //looks for chosen enemy in chosen grotte
        for(Enemy* enemy : currenctEnemies){
            if(chosenEnemy == enemy->getName()){
                int heroLlvBeforeFight = hero.getLevel(); 
                fight(&hero, enemy);
                if(hero.getLevel()-heroLlvBeforeFight == 1){ //hero has leveled one time. Its assumed an enemy doesnt have enough xp to level up twice.
                    makeNewCave(hero, grotter);
                }

                if(hero.erDoed()){
                    exit(0);
                }

                // creating iterator it which points to enemy
                auto it = find(currenctEnemies.begin(), currenctEnemies.end(), enemy);
                if (it != currenctEnemies.end()) { //if it points to enemy in vector
                    cout << "deleting enemy " << enemy->getName() << endl;
                    currenctEnemies.erase(it); //uses erase and iterator to erase enemy
                    delete enemy; //delete enemy to free memory.
                    
                } else {
                    cout << "Enemy not found in the list!" << endl;
                }
                break;
            }

        }

    }
    //while loop is over which means enemies in grotte has been defeated.
    cout << "All enemies in ";
    grotter[grotteChoiceIndex]->showGrotteName();
    cout << " have been defeated!!" << endl;
    hero.gainGold(grotter[grotteChoiceIndex]->getGrotteGold());
    grotter.erase(grotter.begin() + (grotteChoiceIndex));

    //if hero doesnt rise in level, one cave should be created nonetheless
    if(hero.getLevel() == heroLevelAtStart){
        makeNewCave(hero, grotter);
    }
}

//small function creating and pushing grotte to back of grotter vector. 
void makeNewCave(Hero& hero, vector<unique_ptr<Grotte>>& grotter){
    grotter.push_back(make_unique<Grotte>(hero, 3)); //hardcoded 3 to make a cave 3 levels over hero lvl.
}


int main(){

    cout << "Starting game ..." << endl;
    Hero hero; //initialize hero
    startGame(hero); //choosing or creating hero.
    vector<unique_ptr<Grotte>> grotter;

    //make the first 3 caves
    for(int i=1; i<4; i++){
        grotter.push_back(make_unique<Grotte>(hero,i));
    }

    while(true){
        cout << "\n--- Main Menu ---" << endl;
        cout << "1. Show Hero Stats" << endl;
        cout << "2. Show Grotter" << endl;
        cout << "3. Choose grotte" << endl;
        cout << "4. Exit Game" << endl; 

        int choice; //choosing option 1-4
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
            fightInGrotte(hero,grotter);
            if(hero.erDoed()){
                return 0;
            }   
        }
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