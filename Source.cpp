#include "Enemy.h"
#include "MainCharacter.h"
#include "Grotte.h"
#include "DatabaseManager.h"
#include "GameManager.h"

using namespace std;
#include <string>
#include <iostream>
#include <unistd.h>
#include <memory>

int main(int argc, char *argv[]){ //
    QCoreApplication app(argc, argv); // Initialize Qt application

    DatabaseManager dbManager;
    GameManager gameManager(dbManager);

    //initDatabase(); // Initialize the database connection

    cout << "\n*** Welcome to the Terminal Game! ***" << endl;
    Hero hero; //initialize hero
    gameManager.startGame(hero); //choosing or creating hero.
    vector<unique_ptr<Grotte>> grotter;
    int grotteLevel = 3; //used for making new grotte level

    //make the first 3 caves
    for(int i=hero.getLevel(); i<hero.getLevel()+3; i++){
        grotter.push_back(make_unique<Grotte>(hero,i));
    }

    cout << "\n The first 5-8 caves can be defeated without the use of a weapon: Be thoughtful when equipping a weapon, since a weapons durability wont last forever" << endl;


    while(true){
        cout << "\n--- Main Menu ---" << endl;
        cout << "1. Show Hero Stats" << endl;
        cout << "2. Show weapon stats" << endl;
        cout << "3. Equip a weapon" << endl;
        cout << "4. Show Grotter" << endl;
        cout << "5. Choose Grotte" << endl;
        
        cout << " -------------" << endl;
        cout << "6. SQL Analysis" << endl;

        cout << "-------------" << endl;
        cout << "7. Exit Game" << endl;

        cout << "Your choice: ";

        int choice; //choosing option 1-4
        cin >> choice;
        usleep(100000); // 0.1-second delay

        if (choice ==1){
            hero.getStats();
        }
        else if (choice == 2){
            hero.showWeaponStats();
        }
        else if(choice == 3){
            if(hero.hasWeapon()){
                hero.showWeapons();
                cout << "Please choose a weapon by name: " << endl;
                string weaponChoice;
                cin >> weaponChoice;
                hero.equipWeapon(weaponChoice);
            }
            else{
                cout << hero.getName() << " has no weapons yet!!" << endl;
            }
        }


        else if(choice == 4){
            cout << "\n--- Available Grotter ---" << endl;
            for(const auto& grottePtr : grotter){
                const Grotte& grotte = *grottePtr;
                grotte.showGrotteName();
                cout << endl;
            }
        }
        
        else if(choice ==5){
            gameManager.fightInGrotte(hero,grotter, grotteLevel);
            if(hero.erDoed()){
                return 0;
            }   
        }
        else if(choice == 6){
            
            cout << "\nPlease choose an action for SQL analysis:" << endl;

            cout << "\n1. Show heroes alphabetically" << endl;
            cout << "2. Show number of enemies defeated by each hero" << endl;
            cout << "3. For given hero, show number of enemies defeated by weapon" << endl;
            cout << "4. For each weapon type, show hero having most kill with weapon" << endl;
            int SqlChoice;
            cin >> SqlChoice;

            if(SqlChoice == 1){
                dbManager.showHeroesAlphabetically();
            }
            else if(SqlChoice ==2){
                dbManager.showNumberOfEnemiesDefeated();
            }
            else if(SqlChoice ==3){
                dbManager.showHeroesFromDatabase();
                cout << "please choose a name for the hero: " << endl;
                string heroChoice;
                cin >> heroChoice;
                dbManager.showKillByWeaponForHero(heroChoice);
            }
            else if(SqlChoice ==4){
                dbManager.showHeroMostKillsUniqueWeapon();
            }
            else{
                cout << "Invalid choice" << endl;
            }
        }
        else if(choice == 7){
            cout << "Would you like to save hero before exit? [yes] for yes, otherwise no save" << endl;
            string saveHeroChoice; 
            cin >> saveHeroChoice;
            if(saveHeroChoice == "yes"){
                cout << "SAVING HERO...";
                dbManager.saveHeroInDatabase(hero);
                sleep(5);
            }
            cout << "\nExiting game... Goodbye!" << endl;
            return 0;
        }
        else {
            cout << "\nInvalid input: " << choice << ". Please try again!" << endl;
        }
        sleep(1);
    }
    return 0;
}