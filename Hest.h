#pragma once
#include "Enemy.h"

class Hest : public Enemy {
public:
    Hest();
    Hest(int);
    ~Hest();
    string getName() override;
    int getStyrke() override;
};