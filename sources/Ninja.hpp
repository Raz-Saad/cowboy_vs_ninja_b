#pragma once
#include "Character.hpp"
#include <string>
using namespace std;

namespace ariel
{
    class Ninja : public Character
    {
        int speed; // how far can the ninja move

    public:
        Ninja(string name, Point location, int HitPoints, int speed); // constructor
        void move(Character *other);                                  // moves to the other Character the distance that queal to the speed
        void slash(Character *other);                                 // if the ninja is alive and the enemy is 1 meter away from the ninja
                                                                      //, the ninja does 40 dmg
        int getSpeed();                                               // return speed
        string print() override;                                      // add N to the print of Character
    };

}