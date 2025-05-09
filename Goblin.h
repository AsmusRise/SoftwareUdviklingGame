#pragma once
#include "Enemy.h"

class Goblin : public Enemy {
public:
    Goblin();         // Default constructor
    Goblin(int);      // Constructor with modifier
    ~Goblin();        // Destructor
};