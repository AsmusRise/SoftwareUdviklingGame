#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager(){
    initDatabase();
}

void DatabaseManager::initDatabase() { // Function to initialize the database connection
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


void DatabaseManager::showHeroesFromDatabase() { // Function to show all heroes from the database
    QSqlQuery query;
    query.exec("SELECT navn FROM Hero");

    if (!query.isActive()) {
        qDebug() << "Error fetching heroes:" << query.lastError().text();
        return;
    }

    cout << "\n--- Heroes in Database ---" << endl;
    while (query.next()) {
        cout << query.value(0).toString().toStdString() << endl; // Print each hero's name
    }
}


void DatabaseManager::deleteHeroByName(const std::string& heroName) { // Function to delete a hero and their related data from the database
    QSqlQuery query; // Prepare a query to find the hero by name
    query.prepare("SELECT hero_id FROM Hero WHERE navn = :name");
    query.bindValue(":name", QString::fromStdString(heroName));

    if (query.exec() && query.next()) {
        int heroID = query.value(0).toInt(); // Get the hero ID from the query result

        QSqlQuery deleteKillLog;
        deleteKillLog.prepare("DELETE FROM KillLog WHERE hero_id = :heroId");
        deleteKillLog.bindValue(":heroId", heroID);
        deleteKillLog.exec();

        QSqlQuery deleteWeapons;
        deleteWeapons.prepare("DELETE FROM Weapon WHERE hero_id = :heroId");
        deleteWeapons.bindValue(":heroId", heroID);
        deleteWeapons.exec();

        QSqlQuery deleteHero;
        deleteHero.prepare("DELETE FROM Hero WHERE hero_id = :heroId");
        deleteHero.bindValue(":heroId", heroID);
        deleteHero.exec();

        qDebug() << "Deleted existing hero with name:" << QString::fromStdString(heroName);
    }
}


void DatabaseManager::saveHeroInDatabase(Hero& hero){ // Function to save hero and related data to the database
    deleteHeroByName(hero.getName()); //delete already existing hero in database with same name

    //qDebug() << "Is database open:" << QSqlDatabase::database().isOpen();
    //qDebug() << "Driver name:" << QSqlDatabase::database().driverName();

    if (!QSqlDatabase::database().transaction()) {
        qDebug() << "Failed to start transaction:" << QSqlDatabase::database().lastError().text();
        return;
    }

    QSqlQuery query; // Prepare the SQL query to insert the hero data
    query.prepare("INSERT INTO Hero (navn, xp, level, styrke, hp, baseHP, gold) VALUES (:name, :xp, :level, :styrke, :hp, :baseHP, :gold)");

    query.bindValue(":name", QString::fromStdString(hero.getName()));
    query.bindValue(":xp", hero.getXP());
    query.bindValue(":level", hero.getLevel());
    query.bindValue(":styrke", hero.getStyrke());
    query.bindValue(":hp", hero.getHP());
    query.bindValue(":baseHP", hero.getBaseHp()); 
    query.bindValue(":gold", hero.getGold());

    //qDebug() << "Hero INSERT SQL:" << query.lastQuery();
    //qDebug() << "Bound values:" << query.boundValues();
    if (!query.exec()) {
        qDebug() << "Error saving hero to database:" << query.lastError().text();
        QSqlDatabase::database().rollback(); // Rollback the transaction if there is an error
        return;
    }

    //get generated hero_id
    int heroID = query.lastInsertId().toInt(); // Get the ID of the newly inserted hero

    //insert all enemies into KillLogHero. 
    for(const string& enemyName : hero.getHeroKillList()){
        QSqlQuery heroKillLogQuery; // Prepare a query to insert hero's kill log
        heroKillLogQuery.prepare("INSERT INTO KillLogHero (hero_id, enemy_name) VALUES (:heroId, :enemyName)");
        heroKillLogQuery.bindValue(":heroId",heroID);
        heroKillLogQuery.bindValue(":enemyName", QString::fromStdString(enemyName));
        if(!heroKillLogQuery.exec()){
            qDebug() << "Error saving kill" << heroKillLogQuery.lastError().text();
            QSqlDatabase::database().rollback();
            return;
        }
    }
    
    //insert weapons
    for(const Weapon& w : hero.getWeapons()){ // Loop through each weapon of the hero
        QSqlQuery weaponQuery;
        weaponQuery.prepare("INSERT INTO Weapon (navn, skade, styrkeModifier, holdbarhed, hero_id) VALUES (:name, :skade, :styrkeModifier, :holdbarhed, :heroId)");
        weaponQuery.bindValue(":name", QString::fromStdString(w.getName()));
        weaponQuery.bindValue(":skade", w.getSkade());
        weaponQuery.bindValue(":styrkeModifier", w.getStyrkeModifier());
        weaponQuery.bindValue(":holdbarhed", w.getHoldbarhed());
        weaponQuery.bindValue(":heroId", heroID); // Bind the hero ID to the weapon
        if (!weaponQuery.exec()) {
            qDebug() << "Error saving weapon:" << weaponQuery.lastError().text();
            QSqlDatabase::database().rollback(); // Rollback the transaction if there is an error
            return;
        }
        
        int weaponID = weaponQuery.lastInsertId().toInt(); // Get the ID of the newly inserted weapon

        //store every kill of every weapon
        for(const string& enemyName : w.getKillList()){
            QSqlQuery killQuery;
            killQuery.prepare("INSERT INTO KillLogWeapon (hero_id, weapon_id, enemy_name) VALUES (:heroId, :weaponId, :enemyName)");
            killQuery.bindValue(":heroId",heroID);
            killQuery.bindValue(":weaponId", weaponID);
            killQuery.bindValue(":enemyName",QString::fromStdString(enemyName));
            
            if (!killQuery.exec()) {
                qDebug() << "Error saving kill log:" << killQuery.lastError().text();
                QSqlDatabase::database().rollback();
                return;
            }
        }
    }
    if (!QSqlDatabase::database().commit()) { // Commit the transaction
        qDebug() << "Commit failed:" << QSqlDatabase::database().lastError().text();
        return;
    }
    qDebug() << " Hero and related data saved succesfully";
}

Hero DatabaseManager::loadHeroFromDatabase(const string& heroName) { // Function to load hero from database
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
    
        QSqlQuery heroKillListQuery;
        heroKillListQuery.prepare("SELECT enemy_name FROM KillLogHero where hero_id = :heroID");
        heroKillListQuery.bindValue(":heroID", heroID);
        if(heroKillListQuery.exec()){
            while(heroKillListQuery.next()){
                string enemyName = heroKillListQuery.value(0).toString().toStdString();
                hero.addKillToKillList(enemyName);
            }
        }
        else {
            qDebug() << "Error loading hero kill log:" << heroKillListQuery.lastError().text();
        }

        QSqlQuery weaponQuery; // Query to get weapons for the hero
        weaponQuery.prepare("SELECT * FROM Weapon Where hero_id = :heroID"); //
        weaponQuery.bindValue(":heroID", heroID);
        if (weaponQuery.exec()) { // Execute the query
            while (weaponQuery.next()){ // Loop through the results
                string weaponName = weaponQuery.value(1).toString().toStdString();
                int weaponSkade = weaponQuery.value(2).toInt();
                int weaponStyrkeModifier = weaponQuery.value(3).toInt();
                int weaponHoldbarhed = weaponQuery.value(4).toInt();
                Weapon weapon(weaponName, weaponSkade, weaponStyrkeModifier,weaponHoldbarhed);

                // Load kill list for the weapon
                QSqlQuery killQuery;
                killQuery.prepare("SELECT * FROM KillLogWeapon WHERE weapon_id = :weaponID");
                int weaponID = weaponQuery.value(0).toInt();
                killQuery.bindValue(":weaponID", weaponID); // weapon_id
                if (killQuery.exec()) {
                    while (killQuery.next()) {
                        string enemyName = killQuery.value("enemy_name").toString().toStdString();
                        weapon.addToKillList(enemyName); // Add enemy to weapon's kill list
                    }
                }  
                else {
                    qDebug() << "Error loading weapon kill log:" << killQuery.lastError().text();
                }

                hero.getNewWeapon(weapon);  // Add weapon to hero
            }
            
        }
    }
    else {
        qDebug() << "Hero not found in database "<< Qt::endl;;
    }
    return hero;
}

void DatabaseManager::showHeroesAlphabetically() {
    QSqlQuery query;
    if (query.exec("SELECT navn FROM Hero ORDER BY navn ASC;")){
        while (query.next()) {
            QString heroName = query.value(0).toString();
            cout << heroName.toStdString() << endl;
            }
        } 
    else {
        cerr << "Error executing query: " << query.lastError().text().toStdString() << endl;
    }
}

void DatabaseManager::showNumberOfEnemiesDefeated(){
    QSqlQuery query;
    if(query.exec("SELECT Hero.navn AS hero_name, COUNT(KillLogHero.hero_id) AS monsters_defeated FROM Hero LEFT JOIN KillLogHero ON Hero.hero_id = KillLogHero.hero_id GROUP BY Hero.hero_id ORDER BY monsters_defeated DESC;")){
        while (query.next()){
            QString heroName = query.value(0).toString();
            QString monstersDefeated = query.value(1).toString();
            cout << heroName.toStdString() << " has defeated: " << monstersDefeated.toStdString() << " enemies!!" << endl;
        }
    }
    else{
        cerr << "Error executing query: " << query.lastError().text().toStdString() << endl;
    }
}

void DatabaseManager::showKillByWeaponForHero(string hero){
    QSqlQuery query;
    // Prepare the query to find the hero by name
    query.prepare("SELECT navn FROM Hero WHERE navn = :heroName");
    query.bindValue(":heroName", QString::fromStdString(hero));

    if (!query.exec()) {
        qDebug() << "Error fetching heroes:" << query.lastError().text();
        return;
    }

    //if hero is found in database:
    if (query.next()) {
        QSqlQuery queryHeroFound;

        queryHeroFound.prepare(R"(
            SELECT Weapon.navn AS weapon_name, COUNT(KillLogWeapon.weapon_id) AS monsters_defeated
            FROM Weapon
            LEFT JOIN KillLogWeapon ON Weapon.weapon_id = KillLogWeapon.weapon_id
            WHERE Weapon.hero_id = (SELECT hero_id FROM Hero WHERE navn = :heroName)
            GROUP BY Weapon.weapon_id
            ORDER BY monsters_defeated DESC
        )");
        queryHeroFound.bindValue(":heroName", QString::fromStdString(hero));

        if (queryHeroFound.exec()) {
            cout << "\n--- Weapons and Kill Counts for Hero: " << hero << " ---" << endl;
            while (queryHeroFound.next()) {
                QString weaponName = queryHeroFound.value(0).toString();
                int monstersDefeated = queryHeroFound.value(1).toInt();
                cout << "Weapon: " << weaponName.toStdString()
                     << ", Monsters Defeated: " << monstersDefeated << endl;
            }
        } else {
            qDebug() << "Error fetching weapon details:" << queryHeroFound.lastError().text();
        }
    } else {
        cout << "Hero '" << hero << "' not found in the database." << endl;
    }
}

void DatabaseManager::showHeroMostKillsUniqueWeapon(){
    QSqlQuery query;

    // Execute the query
    if (!query.exec(R"(
        WITH RankedHeroes AS (
            SELECT 
                Weapon.weapon_id,
                Weapon.navn AS weapon_name,
                Hero.navn AS hero_name,
                COUNT(KillLogWeapon.log_id) AS kill_count,
                ROW_NUMBER() OVER (PARTITION BY Weapon.weapon_id ORDER BY COUNT(KillLogWeapon.log_id) DESC, Hero.navn ASC) AS rank
            FROM Weapon
            LEFT JOIN KillLogWeapon ON Weapon.weapon_id = KillLogWeapon.weapon_id
            LEFT JOIN Hero ON KillLogWeapon.hero_id = Hero.hero_id
            GROUP BY Weapon.weapon_id, Hero.hero_id
        )
        SELECT 
            weapon_name,
            hero_name,
            kill_count
        FROM RankedHeroes
        WHERE rank = 1
        GROUP BY weapon_name
        ORDER BY weapon_name ASC;
    )")) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    // Fetch and print the results
    while (query.next()) {
        QString weaponName = query.value(0).toString();
        QString heroName = query.value(1).toString();
        int killCount = query.value(2).toInt();

        cout << heroName.toStdString() << " has defeated: " << killCount << " enemies with " << weaponName.toStdString() << "!" << endl;
    }
}



DatabaseManager::~DatabaseManager(){}