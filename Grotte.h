#include "EnemyFactory.h"
#include "MainCharacter.h"

class Grotte{
public:
    Grotte();
    Grotte(const Hero&);
    vector <Enemy*> getEnemyList();
    void showEnemies() const;
    void showGrotteName() const;
    int getGrotteGold() const;
    ~Grotte();
protected:
    vector <Enemy*> enemies;
    string grotteName;
    int grotteGold;
    EnemyFactory factory;
};