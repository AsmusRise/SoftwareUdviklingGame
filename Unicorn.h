#pragma once
#include "Enemy.h"

class Unicorn : public Enemy {
public:
    Unicorn();         // Default constructor
    Unicorn(int);      // Constructor with modifier
    ~Unicorn();        // Destructor
};