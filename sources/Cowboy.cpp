#include "Cowboy.hpp"
#include <stdexcept>
using namespace std;

namespace ariel
{
    // constructor
    Cowboy::Cowboy(string name, Point location) : Character(name, location, 110) // constructor
    {
        this->ammo_amount = 6;
    }

    // shot other Character if cowboy isalive, does 10dmg to him and ammo -1
    void Cowboy::shoot(Character *other)
    {
        if (this == other)
        {
            throw std::runtime_error("coybow can not shot himself");
        }
        if (hasboolets())
        {
            if (this->isAlive() && other->isAlive())
            {
                other->hit(10);
                ammo_amount--;
            }
            else
            {
                throw std::runtime_error("can not shoot, the cowboy is dead or out of ammo");
            }
        }
    }

    // return true if ammo >0
    bool Cowboy::hasboolets()
    {
        if (ammo_amount > 0)
            return true;
        else
            return false;
    }
    
    // insert 6 bullets into ammo_amount
    void Cowboy::reload() 
    {
        if (this->isAlive())
            this->ammo_amount = 6;
        else
            throw std::runtime_error("cowboy is dead, can not reload");
    }

    // return ammo_amount
    int Cowboy::getAmmo_amount()
    {
        return ammo_amount;
    }

    //using the print of character and adding C to the beginning
    string Cowboy::print()
    {
        return "C " + Character::print();
    }
}