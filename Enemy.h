using namespace std;
#include <string>
#include <iostream>
#include <vector>

class Enemy{
public:
    Enemy();
    int angrib();
    void tagSkade(int);
    ~Enemy();
public:
    string navn;
    int hp;
    int styrke;
    int xp;
};