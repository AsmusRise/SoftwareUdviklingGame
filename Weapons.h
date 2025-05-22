using namespace std;
#include <string>

class Weapon
{
protected:
    string name;
    int skade;
    int styrkeModifier;
    int holdbarhed;
public:
    Weapon();
    Weapon(string n, int s, int sM, int h);

    //get metoder
    int getSkade() const;
    string getName() const;
    int getStyrkeModifier() const;
    int getHoldbarhed() const;

    void use(); //decreases holbarhed
    bool hasHolbarhed();
    ~Weapon();
};