#pragma once
#include "Charachter.hpp"
#include <string>
using namespace std;

namespace ariel
{
    class Ninja : public Charachter
    {
        int speed;

    public:
        Ninja(string name, Point location, int HitPoints, int speed); // constructor
        void move(Charachter *other);                                 // moves to the other characther the distance that queal to the speed
        void slash(Charachter *other);                                // if the ninja is alive and the enemy is 1 meter away from the ninja
                                                                      //, the ninja does 40 dmg
        int getSpeed();                                               // return speed
        string print();                                               // add N to the print of charachter
    };

}