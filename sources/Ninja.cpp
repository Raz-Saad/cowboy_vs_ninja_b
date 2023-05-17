#include "Ninja.hpp"
#include <stdexcept>
using namespace std;

namespace ariel
{
    Ninja::Ninja(string name, Point location, int HitPoints, int speed) : Charachter(name, location, HitPoints) // constructor
    {
        this->speed = speed;
    }
    void Ninja::move(Charachter *other)
    {
        this->setLocation(Point::moveTowards(this->getLocation(), other->getLocation(), speed));
    }
    void Ninja::slash(Charachter *other)
    {
        if (this->isAlive() && this->distance(other) <= 1)
        {
            other->hit(40);
        }
        else
        {
            throw std::runtime_error("can not slash,ninja is dead or the enemy is too far");
        }
    }
    // return speed
    int Ninja::getSpeed()
    {
        return speed;
    }
    string Ninja::print()
    {
        return "N "+Charachter::print();
    }
}