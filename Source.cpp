#include "Enemy.h"
#include "MainCharacter.h"
#include "Grotte.h"

using namespace std;
#include <string>
#include <iostream>
#include <unistd.h>
#include <memory>

// Include necessary SQL headers
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>

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

                hero.addKillToWeaponKillList(enemy->getName()); // Add enemy to weapon's kill list
                hero.addToHeroKillList(enemy->getName()); // Add enemy to hero's kill list

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
    if(grotter[grotteChoiceIndex]->isWeaponInGrotte()){
        cout << "Weapon was found in grotte" << endl;
        hero.getNewWeapon(grotter[grotteChoiceIndex]->getWeapon());
    }
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

// int findAvailableHeroID(){
//     QSqlQuery query;
//     query.prepare
// }

Hero loadHeroFromDatabase(string heroName) { // Function to load hero from database
    Hero hero;
    QSqlQuery query;
    query.prepare("SELECT * FROM Hero WHERE navn = :name");
    query.bindValue(":name", QString::fromStdString(heroName));
    if (query.exec() && query.next()) {
        int heroID = query.value(0).toInt();
        hero.chooseNameByCode(query.value(1).toString().toStdString());
        hero.gainXP(query.value(2).toInt());
        hero.setLevel(query.value(3).toInt());
        hero.setStyrke(query.value(4).toInt());
        hero.setHP(query.value(5).toInt());
        hero.setBaseHP(query.value(6).toInt());
        hero.gainGold(query.value(7).toInt());
    

        QSqlQuery weaponQuery; // Query to get weapons for the hero
        weaponQuery.prepare("SELECT * FROM Weapon Where hero_id = heroID"); //
        weaponQuery.bindValue(":heroID", heroID);
        if (weaponQuery.exec()) { // Execute the query
            while (weaponQuery.next()){ // Loop through the results
                string weaponName = weaponQuery.value(1).toString().toStdString();
                int weaponSkade = weaponQuery.value(2).toInt();
                int weaponStyrkeModifier = weaponQuery.value(3).toInt();
                int weaponHoldbarhed = weaponQuery.value(4).toInt();
                Weapon weapon(weaponName, weaponSkade, weaponStyrkeModifier,weaponHoldbarhed);
                hero.getNewWeapon(weapon);  // Add weapon to hero
            }
        }
    }
    else {
        qDebug() << "Hero not found in database "<< Qt::endl;;
    }
    return hero;
}

void saveHeroInDatabase(Hero& hero){

    qDebug() << "Is database open:" << QSqlDatabase::database().isOpen();
    qDebug() << "Driver name:" << QSqlDatabase::database().driverName();

    
    QSqlQuery query;
    query.prepare("INSERT INTO Hero (navn, xp, level, styrke, hp, baseHP, gold) VALUES (:name, :xp, :level, :styrke, :hp, :baseHP, :gold)");

    query.bindValue(":name", QString::fromStdString(hero.getName()));
    query.bindValue(":xp", hero.getXP());
    query.bindValue(":level", hero.getLevel());
    query.bindValue(":styrke", hero.getStyrke());
    query.bindValue(":hp", hero.getHP());
    query.bindValue(":baseHP", hero.getBaseHp()); 
    query.bindValue(":gold", hero.getGold());

    qDebug() << "Hero INSERT SQL:" << query.lastQuery();
    qDebug() << "Bound values:" << query.boundValues();
    if (!query.exec()) {
        qDebug() << "Error saving hero to database:" << query.lastError().text();
    }

    //get generated hero_id
    int heroID = query.lastInsertId().toInt(); // Get the ID of the newly inserted hero

    //insert weapons
    for(Weapon w : hero.getWeapons()){
        QSqlQuery weaponQuery;
        weaponQuery.prepare("INSERT INTO Weapon (navn, skade, styrkeModifier, holdbarhed, hero_id) VALUES (:name, :skade, :styrkeModifier, :holdbarhed, :heroId)");
        weaponQuery.bindValue(":name", QString::fromStdString(w.getName()));
        weaponQuery.bindValue(":skade", w.getSkade());
        weaponQuery.bindValue(":styrkeModifier", w.getStyrkeModifier());
        weaponQuery.bindValue(":holdbarhed", w.getHoldbarhed());
        weaponQuery.bindValue(":heroId", heroID); // Bind the hero ID to the weapon
        if(!weaponQuery.exec()){
            qDebug() << "Weapon values:" << weaponQuery.boundValues();
            //qDebug() << "Error saving weapon to database: " << weaponQuery.lastError().text();
            continue;
        }
        
        int weaponID = weaponQuery.lastInsertId().toInt(); // Get the ID of the newly inserted weapon

        //store every kill of every weapon
        for(string enemyName : w.getKillList()){
            QSqlQuery killQuery;
            killQuery.prepare("INSERT INTO KillLog (hero_id, weapon_id, enemy_name) VALUES (:heroId, :weaponId, :enemyName)");
            killQuery.bindValue(":heroId",heroID);
            killQuery.bindValue(":weaponId", weaponID);
            killQuery.bindValue(":enemyName",QString::fromStdString(enemyName));
            
            if(!killQuery.exec()){
                qDebug() << "Error saving kill log: " << killQuery.lastError().text();
            }
        }
    }
}

void initDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("GameData.db");
    db.open();

    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
        exit(1);
    } else {
        qDebug() << "Database opened successfully.";
    }

    // Sanity test: Can we SELECT from the database?
    QSqlQuery testQuery;
    bool selectOK = testQuery.exec("SELECT name FROM sqlite_master WHERE type='table'");
    if (!selectOK) {
        qDebug() << "SELECT failed:" << testQuery.lastError().text();
    } else {
        qDebug() << "Tables:";
        while (testQuery.next()) {
            qDebug() << " -" << testQuery.value(0).toString();
        }
    }
}

int main(int argc, char *argv[]){
    QCoreApplication app(argc, argv);
    initDatabase();

    cout << "\n*** Welcome to the Terminal Game! ***" << endl;
    Hero hero; //initialize hero
    startGame(hero); //choosing or creating hero.
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
        cout << "6. Exit Game" << endl;
        cout << "7. Manual test insert" << endl;
        cout << "Your choice: ";

        int choice; //choosing option 1-4
        cin >> choice;
        usleep(100000); // 0.1-second delay

        if (choice ==1){
            hero.getStats();
        }
        if (choice == 2){
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
            fightInGrotte(hero,grotter, grotteLevel);
            if(hero.erDoed()){
                return 0;
            }   
        }
        else if(choice == 6){
            cout << "Would you like to save hero before exit?" << endl;
            string saveHeroChoice; 
            cin >> saveHeroChoice;
            if(saveHeroChoice == "yes"){
                cout << "SAVING HERO...";
                saveHeroInDatabase(hero);
                sleep(5);
            }

            cout << "\nExiting game... Goodbye!" << endl;
            return 0;
        }
        if(choice == 7){
            QSqlQuery test;

            // Print out which driver is being used and whether the DB is open
            qDebug() << "Driver name:" << QSqlDatabase::database().driverName();
            qDebug() << "Is database open:" << QSqlDatabase::database().isOpen();

            // Prepare the insert query
            bool prepareSuccess = test.prepare(
                "INSERT INTO Hero (navn, xp, level, styrke, hp, baseHP, gold) "
                "VALUES (:name, :xp, :level, :styrke, :hp, :baseHP, :gold)"
            );
            
            if (!prepareSuccess) {
                qDebug() << "Prepare failed:" << test.lastError().text();
                return 0;
            }

            // Bind values
            test.bindValue(":name", "TestHero");
            test.bindValue(":xp", 0);
            test.bindValue(":level", 1);
            test.bindValue(":styrke", 2);
            test.bindValue(":hp", 10);
            test.bindValue(":baseHP", 10);
            test.bindValue(":gold", 0);

            // Log query & bindings
            qDebug() << "Query to execute:" << test.lastQuery();
            qDebug() << "Bound values:" << test.boundValues();

            // Execute
            if (!test.exec()) {
                qDebug() << "Insert failed:" << test.lastError().text();
            } else {
                qDebug() << "Insert successful!";
            }
        }

        else if(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice !=5){
            cout << "\nInvalid input: " << choice << ". Please try again!" << endl;
        }
        sleep(1);

    }


    return 0;
}