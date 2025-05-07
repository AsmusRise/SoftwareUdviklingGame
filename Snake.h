#pragma once
#include "Enemy.h"

class Snake : public Enemy {
public:
    Snake();
    Snake(int);
    string getName() override;
    ~Snake();
};