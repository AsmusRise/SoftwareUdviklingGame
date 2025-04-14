#pragma once
using namespace std;
#include <string>
#include <iostream>
#include <vector>

class Enemy{
public:
    Enemy();
    Enemy(string);
    string getName();
    int angrib();
    void tagSkade(int);
    int getXP();
    bool erDoed();
    ~Enemy();
public:
    string navn;
    int hp;
    int styrke;
    int xp;
};