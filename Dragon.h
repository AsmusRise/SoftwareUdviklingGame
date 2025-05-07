#pragma once
#include "Enemy.h"

class Dragon : public Enemy {
public:
    Dragon();         // Default constructor
    Dragon(int);      // Constructor with modifier
    string getName() override;
    ~Dragon();        // Destructor
};