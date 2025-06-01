
#include "GameManager.h"
#include <iostream>
#include <unistd.h>

GameManager::GameManager(DatabaseManager& dbManager) : dbManager(dbManager) {}

void GameManager::startGame(Hero& hero){
    string valg;
    while(true){
        cout << "Would you like to create a new hero, choose an existing one or load from database?" << endl;
        cout << "Type [choose] to select a hero, [load] to load a hero or [create] to create a new one." << endl;
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
        else if(valg =="load"){
            while(hero.getName() =="empty"){
                string heroValg;
                dbManager.showHeroesFromDatabase(); // Show all heroes in the database
                cout << "Please choose a hero by name" << endl;
                cin >> heroValg; 
                hero = dbManager.loadHeroFromDatabase(heroValg);
                if(hero.getName() == "empty"){
                    cout << "Please choose a valid name" << endl;
                }
                if(hero.getName() ==heroValg){
                    return;
                }
            }
        }
        cout <<"invalid option, please try again! " << endl;
        sleep(0.5);
    }
}


void GameManager::fight(Hero* hero, Enemy* enemy){
    //function to fight between hero and enemy
    // The `validfight` variable ensures the fight continues until either the hero or the enemy is defeated.
    bool validfight = true;
    while(validfight){
        cout << "\n" << hero->getName() << " attacks " << enemy->getName() << "!" << endl;
        enemy->tagSkade(hero->attack());
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


void GameManager::fightInGrotte(Hero& hero, vector<unique_ptr<Grotte>>& grotter, int& grotteLevel){
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
    vector<Enemy*>& currenctEnemies = grotter[grotteChoiceIndex]->getEnemyList();
    while (grotter[grotteChoiceIndex]->grottePopulated()) { // Check if enemies are alive in the cave
        cout << "\n--- Enemies in ";
        grotter[grotteChoiceIndex]->showGrotteName();
        cout << " ---" << endl;

        grotter[grotteChoiceIndex]->showEnemies();
        cout << "\nChoose an enemy to fight: ";
        int chosenEnemyIndex;
        cin >> chosenEnemyIndex;

        // Look for chosen enemy in chosen grotte
        if(chosenEnemyIndex <1 || chosenEnemyIndex >currenctEnemies.size()){
            cout << "invalid enemy index. Please try again" << endl;
            continue;
        }
        
        Enemy* enemy =  currenctEnemies[chosenEnemyIndex-1];
        cout << "You have chosen to fight: " << enemy->getName() << endl;

        int heroLlvBeforeFight = hero.getLevel();
        fight(&hero, enemy);

        if (hero.getLevel() - heroLlvBeforeFight == 1) { // Hero has leveled up
            cout << "\n!!! " << hero.getName() << " leveled up! A new cave has been created. !!!" << endl;
            makeNewCave(hero, grotter, grotteLevel);
        }

        if (hero.erDoed()) {
            exit(0);
        }

        cout << "Enemy name: " << enemy->getName() << endl; // debug statement
        hero.addKillToKillList(enemy->getName()); // Add enemy to hero kill list. If weapon equipped, weapon also gets added kill.
        

        // Remove defeated enemy
        currenctEnemies.erase(currenctEnemies.begin() +(chosenEnemyIndex -1));
        delete enemy;
    }

    // If all enemies in the grotte have been defeated
    if(!grotter[grotteChoiceIndex]->grottePopulated()){
    
        cout << "\n!!! All enemies in ";
        grotter[grotteChoiceIndex]->showGrotteName();
        cout << " have been defeated! !!!" << endl;
        hero.gainGold(grotter[grotteChoiceIndex]->getGrotteGold());
        if(grotter[grotteChoiceIndex]->isWeaponInGrotte()){
            cout << "Weapon was found in grotte" << endl;
            hero.getNewWeapon(grotter[grotteChoiceIndex]->getWeapon());
        }
        grotter.erase(grotter.begin() + grotteChoiceIndex);
    }
    // If hero doesn't rise in level, one cave should be created nonetheless
    if (hero.getLevel() == heroLevelAtStart && grotter.size() < 4) {
        cout << "\nA new cave has been created!" << endl;
        makeNewCave(hero, grotter, grotteLevel);
    }
}


void GameManager::makeNewCave(Hero& hero, vector<unique_ptr<Grotte>>& grotter, int& grotteLevel){
    // Increment the grotte level for the new grotte
    grotteLevel++;

    // Create and add the new grotte
    grotter.push_back(make_unique<Grotte>(hero, grotteLevel));
    cout << "A new grotte (Level " << grotteLevel << ") has been created!" << endl;
}

GameManager::~GameManager(){}