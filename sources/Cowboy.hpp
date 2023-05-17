#pragma once
#include "Charachter.hpp"
using namespace std;

namespace ariel
{
    class Cowboy : public Charachter
    {
        int ammo_amount;

    public:
        Cowboy(string name, Point location); // constructor
        void shoot(Charachter *other);       // shot other Charachter if cowboy isalive, does 10dmg to him and ammo -1
        bool hasboolets();                   // return true if ammo >0
        void reload();                       // insert 6 bullets into ammo_amount
        int getAmmo_amount();                // return ammo_amount
    };

}