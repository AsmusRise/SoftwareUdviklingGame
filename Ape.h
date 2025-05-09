#pragma once
#include "Enemy.h"

class Ape : public Enemy {
public:
    Ape();         // Default constructor
    Ape(int);      // Constructor with modifier
    ~Ape();        // Destructor
};