#pragma once
using namespace std;
#include <unistd.h> //used for sleep function
#include <iostream>
#include <string>
#include <vector>
#include "Weapons.h"

class Hero{
public: 
    Hero();
    void setName();
    void chooseNameByCode(string);
    void chooseHero();
    int attack(); //figthing logic
    void takeDamage(int); //figthing logic
    void levelUp();
    void gainXP(int); //figthing logic
    void gainGold(int);
    void showHeroes();
    void addToHeroKillList(string enemyName); //used to add enemy to kill list

    //methods used for SQL database
    void setLevel(int);
    void setStyrke(int);
    void setBaseHP(int);
    void setHP(int); //used to reset hp


    //get metoder:
    string getName() const;
    int getXP() const; //used for gaining xp logic
    int getLevel() const; 
    int getStyrke() const; //used in fighting logic
    int getHP() const; //used in fighting logic
    int getBaseHp() const;
    int getGold() const; //used to see hero gold.
    void getStats(); //used to see all stats

    

    void getNewWeapon(Weapon); //used to add weapon to hero
    void equipWeapon(const string); //used to equip a weapon
    bool isWeaponEquipped(); //used to see if a weapon is equipped
    void showWeapons() const; //used to show all weapons
    bool hasWeapon() const; //used to see if hero has a weapon
    vector<Weapon> getWeapons() const; //used to get all weapons
    void showWeaponStats() const; //function for showing weapon stats
    void addKillToKillList(string enemyName); //used to add enemy to weapon kill list
    vector<string> getHeroKillList() const;



    bool erDoed(); //returns false if hero is alive.
    ~Hero();
    
private:
    string navn;       // The hero's name.
    int xp;            // The hero's current XP.
    int level;         // The hero's current level.
    int styrke;        // The hero's strength (used for attacking enemies).
    int hp;            // The hero's current HP.
    int baseHP;        // The hero's base HP (used to reset HP after a fight).
    int gold;          // The hero's current gold.
    vector<string> heroes; // A list of available hero names.
    vector<Weapon> weapons;
    Weapon* currentWeapon;
    vector<string> heroKillList;   // A list of enemies the hero has defeated.
};