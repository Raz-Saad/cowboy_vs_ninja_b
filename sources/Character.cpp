#include "Character.hpp"
#include <stdexcept>
#include <iostream>
using namespace std;

namespace ariel
{
    Character::Character(string name, Point location, int HitPoints)
    {
        this->location = location;
        this->name = name;
        this->HitPoints = HitPoints;
    }
    Character::Character()
    {
    }

    bool Character::isAlive() // return true if hitpoint > 0
    {
        if (HitPoints > 0)
            return true;
        else
            return false;
    }
    double Character::distance(Character *other) // return the distance bettwen the Charachters
    {
        return location.distance(other->getLocation());
    }
    void Character::hit(int amount) // substract amount from hitpoints
    {
        if (amount >= 0)
            HitPoints -= amount;
        else
            throw std::invalid_argument("can not do minus damage");
    }
    string Character::getName() // return the name of the Charachter
    {
        return name;
    }
    int Character::geHitPoints() // return the hp of a Charachter
    {
        return HitPoints;
    }
    Point Character::getLocation() // return the location of a Charachter
    {
        return location;
    }
    string Character::print() // prints name,hp,location (look on git)
    {
        string alive = this->getName() + "," + to_string(this->geHitPoints()) + "," + this->getLocation().print();
        string dead = "(" + this->getName() + ")," + this->getLocation().print();

        if (this->isAlive())
            return alive;
        else
            return dead;
    }

    void Character::setLocation(Point location)
    {
        this->location = location;
    }

    void Character::setIn_Team(bool flag)
    {
        this->in_team = flag;
    }

    bool Character::getIn_Team()
    {
        return this->in_team;
    }
}