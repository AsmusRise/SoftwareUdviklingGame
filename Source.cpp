#include "Enemy.h"
#include "MainCharacter.h"
#include "Grotte.h"
using namespace std;
#include <string>
#include <iostream>
#include <unistd.h>
#include <memory>

void makeNewCave(Hero& hero, vector<unique_ptr<Grotte>>& grotter, int& grotteLevel);

void startGame(Hero& hero){ //function to initialize hero by create or choosing.
    string valg;
    while(true){
        cout << "Would you like to create a new hero or choose an existing one?" << endl;
        cout << "Type [choose] to select a hero or [create] to create a new one." << endl;
        cout << "Your choice: ";
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
        sleep(0.5);
    }
}

void fight(Hero* hero, Enemy* enemy){ 
    //function to fight between hero and enemy
        // The `validfight` variable ensures the fight continues until either the hero or the enemy is defeated.
    bool validfight = true;
    while(validfight){
        cout << "\n" << hero->getName() << " attacks " << enemy->getName() << "!" << endl;
        enemy->tagSkade(hero->getStyrke());
        //sleep(1);

        if(enemy->erDoed()){
            //hero gets xp, and hp is reset (hero heals back up)
            cout << "\n!!! " << hero->getName() << " has defeated " << enemy->getName() << " !!!" << endl;
            hero->gainXP(enemy->getXP());
            validfight = false;
            break;
        }
        cout << enemy->getName() << " attacks back!" << endl;
        hero->takeDamage(enemy->angrib());
        //sleep(1);
        
        //checks if hero is dead
        if(hero->erDoed()){ //checks if hero is dead after attack
            cout << "\n!!! " << hero->getName() << " has died. Better luck next time! !!!" << endl;
            cout << "Enemy remaining HP: " << enemy->getHP() << endl;
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
void fightInGrotte(Hero& hero, vector<unique_ptr<Grotte>>& grotter, int& grotteLevel) {
    int heroLevelAtStart = hero.getLevel();
    int grotteChoice = 0;

    // Prompt user to choose a valid grotte
    while (true) {
        cout << "\n--- Available Grotter ---" << endl;
        for (int i = 0; i < grotter.size(); i++) {
            grotter[i]->showGrotteName();
            cout << "\n";
        }
        cout << "\nChoose a grotte by level number: ";
        cin >> grotteChoice;

        // Check if the chosen grotte exists
        bool validChoice = false;
        for (int i = 0; i<grotter.size(); i++) {
            cout << "Showing grotte levels: ";
            cout << grotter[i]->getGrotteLevel();
            cout << endl;
            if (grotter[i]->getGrotteLevel() == grotteChoice) {
                
                validChoice = true;
                break;
            }
        }

        if (validChoice) {
            break; // Exit the loop if the choice is valid
        } else {
            cout << "Invalid grotte choice. Please try again!" << endl;
        }
        sleep(1);
    }

    int grotteChoiceIndex =-1;
    // Look for the chosen grotte in the vector of grotter
    for (int i = 0; i < grotter.size(); i++) {
        if (grotter[i]->getGrotteLevel() == grotteChoice) {
            cout << "You have chosen: ";
            grotter[i]->showGrotteName();
            cout << endl;
            grotteChoiceIndex = i;
            sleep(1);
            break;
        }
    }

    // Check if a valid grotte was found
    if (grotteChoiceIndex == -1) {
        cout << "Error: Grotte not found. Returning to main menu." << endl;
        return; // Exit the function if no valid grotte was found
    }

    // Choosing an enemy in the grotte
    string chosenEnemy;
    vector<Enemy*>& currenctEnemies = grotter[grotteChoiceIndex]->getEnemyList();
    while (grotter[grotteChoiceIndex]->grottePopulated()) { // Check if enemies are alive in the cave
        cout << "\n--- Enemies in ";
        grotter[grotteChoiceIndex]->showGrotteName();
        cout << " ---" << endl;

        grotter[grotteChoiceIndex]->showEnemies();
        cout << "\nChoose an enemy to fight: ";
        cin >> chosenEnemy;

        // Look for chosen enemy in chosen grotte
        for (Enemy* enemy : currenctEnemies) {
            if (chosenEnemy == enemy->getName()) {
                int heroLlvBeforeFight = hero.getLevel();
                fight(&hero, enemy);
                if (hero.getLevel() - heroLlvBeforeFight == 1) { // Hero has leveled up
                    cout << "\n!!! " << hero.getName() << " leveled up! A new cave has been created. !!!" << endl;
                    makeNewCave(hero, grotter, grotteLevel);
                }

                if (hero.erDoed()) {
                    exit(0);
                }

                // Remove defeated enemy
                auto it = find(currenctEnemies.begin(), currenctEnemies.end(), enemy);
                if (it != currenctEnemies.end()) {
                    currenctEnemies.erase(it);
                    delete enemy;
                } else {
                    cout << "Enemy not found!" << endl;
                }
                break;
            }
        }
    }

    // All enemies in the grotte have been defeated
    cout << "\n!!! All enemies in ";
    grotter[grotteChoiceIndex]->showGrotteName();
    cout << " have been defeated! !!!" << endl;
    hero.gainGold(grotter[grotteChoiceIndex]->getGrotteGold());
    grotter.erase(grotter.begin() + grotteChoiceIndex);

    // If hero doesn't rise in level, one cave should be created nonetheless
    if (hero.getLevel() == heroLevelAtStart && grotter.size() < 4) {
        cout << "\nA new cave has been created!" << endl;
        makeNewCave(hero, grotter, grotteLevel);
    }
}

//small function creating and pushing grotte to back of grotter vector. 
void makeNewCave(Hero& hero, vector<unique_ptr<Grotte>>& grotter, int& grotteLevel) {
    // Increment the grotte level for the new grotte
    grotteLevel++;

    // Create and add the new grotte
    grotter.push_back(make_unique<Grotte>(hero, grotteLevel));
    cout << "A new grotte (Level " << grotteLevel << ") has been created!" << endl;
}


int main(){
    cout << "\n*** Welcome to the Terminal Game! ***" << endl;
    Hero hero; //initialize hero
    startGame(hero); //choosing or creating hero.
    vector<unique_ptr<Grotte>> grotter;
    int grotteLevel = 3; //used for making new grotte level

    //make the first 3 caves
    for(int i=1; i<4; i++){
        grotter.push_back(make_unique<Grotte>(hero,i));
    }

    while(true){
        cout << "\n--- Main Menu ---" << endl;
        cout << "1. Show Hero Stats" << endl;
        cout << "2. Show Grotter" << endl;
        cout << "3. Choose Grotte" << endl;
        cout << "4. Exit Game" << endl;
        cout << "Your choice: ";

        int choice; //choosing option 1-4
        cin >> choice;
        usleep(100000); // 0.1-second delay

        if (choice ==1){
            hero.getStats();
        }
        else if(choice == 2){
            cout << "\n--- Available Grotter ---" << endl;
            for(const auto& grottePtr : grotter){
                const Grotte& grotte = *grottePtr;
                grotte.showGrotteName();
                cout << endl;
            }
        }
        
        else if(choice ==3){
            fightInGrotte(hero,grotter, grotteLevel);
            if(hero.erDoed()){
                return 0;
            }   
        }
        else if(choice == 4){
            cout << "\nExiting game... Goodbye!" << endl;
            return 0;
        }
        else if(choice != 1 && choice != 2 && choice != 3 && choice != 4){
            cout << "\nInvalid input: " << choice << ". Please try again!" << endl;
        }
        sleep(1);

    }


    return 0;
}