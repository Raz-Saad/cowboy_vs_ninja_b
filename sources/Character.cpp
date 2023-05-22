#include "Character.hpp"
#include <stdexcept>
#include <limits.h>
#include <iostream>
using namespace std;

namespace ariel
{
    // constructor
    Character::Character(string name, Point location, int HitPoints)
    {
        this->location = location;
        this->name = name;
        this->HitPoints = HitPoints;
        this->in_team = false;
        this->did_action = false;
    }

    // empty constructor
    Character::Character()
    {
    }

    // return true if hitpoint > 0
    bool Character::isAlive()
    {
        if (HitPoints > 0)
            return true;
        else
            return false;
    }

    // return the distance bettwen the Charachters
    double Character::distance(Character *other)
    {
        return location.distance(other->getLocation());
    }

    // substract amount from hitpoints
    void Character::hit(int amount)
    {
        if (amount >= 0)
            HitPoints -= amount;
        else
            throw std::invalid_argument("can not do minus damage");
    }

    // return the name of the Charachter
    string Character::getName()
    {
        return name;
    }

    // return the hp of a Charachter
    int Character::geHitPoints()
    {
        return HitPoints;
    }

    // return the location of a Charachter
    Point Character::getLocation()
    {
        return location;
    }

    // prints name,hp,location
    string Character::print()
    {
        string alive = this->getName() + "," + to_string(this->geHitPoints()) + "," + this->getLocation().print();
        string dead = "(" + this->getName() + ")," + this->getLocation().print();

        if (this->isAlive())
            return alive;
        else
            return dead;
    }

    // set a location to the Character
    void Character::setLocation(Point location)
    {
        this->location = location;
    }

    // set if a Character is in a team or not
    void Character::setIn_Team(bool flag)
    {
        this->in_team = flag;
    }

    // get if a Character is in a team or not
    bool Character::getIn_Team()
    {
        return this->in_team;
    }

    // set if a Character did an action in a turn
    void Character::setDid_action(bool flag)
    {
        did_action = flag;
    }

    // get if a Character did an action in a turn
    bool Character::getDid_action()
    {
        return did_action;
    }

}