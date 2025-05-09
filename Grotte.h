#include "EnemyFactory.h"
#include "MainCharacter.h"

class Grotte{
public:
    Grotte();
    Grotte(const Hero&, float);
    vector <Enemy*>& getEnemyList();
    void showEnemies() const;
    void showGrotteName() const;
    int getGrotteGold() const;
    bool grottePopulated() const;
    ~Grotte();
protected:
    vector <Enemy*> enemies;
    string grotteName;
    int grotteGold;
    EnemyFactory factory;
};