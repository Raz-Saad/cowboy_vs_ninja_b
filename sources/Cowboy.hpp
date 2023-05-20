#pragma once
#include "Character.hpp"
#include <string>
using namespace std;

namespace ariel
{
    class Cowboy : public Character
    {
        int ammo_amount;

    public:
        Cowboy(string name, Point location); // constructor
        void shoot(Character *other);       // shot other Character if cowboy isalive, does 10dmg to him and ammo -1
        bool hasboolets();                   // return true if ammo >0
        void reload();                       // insert 6 bullets into ammo_amount
        int getAmmo_amount();                // return ammo_amount
        string print() override;                      // add C to the print of Character
    };

}