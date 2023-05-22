#include "Ninja.hpp"
#include <stdexcept>
using namespace std;

namespace ariel
{
    // constructor
    Ninja::Ninja(string name, Point location, int HitPoints, int speed) : Character(name, location, HitPoints) // constructor
    {
        this->speed = speed;
    }

    // moves to the other Character the distance that queal to the speed
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

    // if the ninja is alive and the enemy is 1 meter away from the ninja,the ninja does 40 dmg
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

    // using the print of character and adding C to the beginning
    string Ninja::print()
    {
        return "N " + Character::print();
    }
}