#include "EnemyFactory.h"

class Grotte{
public:
    Grotte();
    void showEnemies();
    ~Grotte();
protected:
    EnemyFactory enemies;
};