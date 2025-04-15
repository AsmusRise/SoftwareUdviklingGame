#include "Enemies.h"
#include <algorithm>

string normalizeString(const string& input) {
    string result = input;
    // Convert to lowercase
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    // Trim leading and trailing spaces
    result.erase(0, result.find_first_not_of(" \t\n\r"));
    result.erase(result.find_last_not_of(" \t\n\r") + 1);
    return result;
}

Enemies::Enemies(){}

Enemies::Enemies(vector<Enemy*> e){
    enemies = e;
}

void Enemies::printNames(){
    for(int i =0; i<enemies.size();i++){
        cout << enemies[i]->getName() << "          Styrke:  " << enemies[i]->getStyrke() << "         HP: " << enemies[i]->getHP() << endl;

    }
    cout << "- - - - - - " << endl;
}

void Enemies::addEnemy(Enemy* e) {
    enemies.push_back(e); // Add the Enemy pointer to the vector
}

Enemy* Enemies::getEnemy(const string& n){
    for(Enemy* enemy : enemies){
        cout << "Comparing input " << normalizeString(n) << " with " << normalizeString(enemy->getName()) << endl;
        if(normalizeString(enemy->getName()) == normalizeString(n)){
            return enemy;
        }
    }
    return nullptr;
}



Enemies::~Enemies(){}