#include "Ninja.hpp"
#include <stdexcept>
using namespace std;

namespace ariel
{
    Ninja::Ninja(string name, Point location, int HitPoints, int speed) : Character(name, location, HitPoints) // constructor
    {
        this->speed = speed;
    }
    void Ninja::move(Character *other)
    {
        if (this == other || this->isAlive() == false)
        {
            throw std::runtime_error("ninja is dead or trying to move towards himself");
        }
        else
        {
            this->setLocation(Point::moveTowards(this->getLocation(), other->getLocation(), speed));
        }
    }
    void Ninja::slash(Character *other)
    {
        if (this == other)
        {
            throw std::runtime_error("ninja can not slash himself");
        }

        if (this->distance(other) <= 1)
        {
            if (this->isAlive() && other->isAlive())
                other->hit(40);
            else
                throw std::runtime_error("can not slash,ninja is dead or enemy is dead ");
        }
    }

    // return speed
    int Ninja::getSpeed()
    {
        return speed;
    }
    string Ninja::print()
    {
        return "N " + Character::print();
    }
}