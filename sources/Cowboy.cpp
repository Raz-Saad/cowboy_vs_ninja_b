#include "Cowboy.hpp"
#include <stdexcept>
using namespace std;

namespace ariel
{
    Cowboy::Cowboy(string name, Point location) : Charachter(name, location, 110) // constructor
    {
        this->ammo_amount = 6;
    }
    void Cowboy::shoot(Charachter *other)
    {
        if (this->isAlive() && hasboolets())
        {
            other->hit(10);
            ammo_amount--;
        }
        else
        {
            throw std::runtime_error("can not shoot, the cowboy is dead or out of ammo");
        }
    }
    // shot other Charachter if cowboy isalive, does 10dmg to him and ammo -1
    bool Cowboy::hasboolets()
    {
        if (ammo_amount > 0)
            return true;
        else
            return false;
    }
    // return true if ammo >0
    void Cowboy::reload() // insert 6 bullets into ammo_amount
    {
        this->ammo_amount = 6;
    }
    // return ammo_amount
    int Cowboy::getAmmo_amount()
    {
        return ammo_amount;
    }
    string Cowboy::print()
    {
        return "C " + Charachter::print();
    }
}