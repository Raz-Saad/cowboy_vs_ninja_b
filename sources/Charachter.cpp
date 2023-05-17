#include "Charachter.hpp"
using namespace std;
#include <iostream>
namespace ariel
{
    Charachter::Charachter(string name, Point location, int HitPoints)
    {
        this->location = location;
        this->name = name;
        this->HitPoints = HitPoints;
    }
    Charachter::Charachter()
    {
    }

    bool Charachter::isAlive() // return true if hitpoint > 0
    {
        if (HitPoints > 0)
            return true;
        else
            return false;
    }
    double Charachter::distance(Charachter *other) // return the distance bettwen the Charachters
    {
        return location.distance(other->getLocation());
    }
    void Charachter::hit(int amount) // substract amount from hitpoints
    {
        HitPoints -= amount;
    }
    string Charachter::getName() // return the name of the Charachter
    {
        return name;
    }
    int Charachter::geHitPoints() // return the hp of a Charachter
    {
        return HitPoints;
    }
    Point Charachter::getLocation() // return the location of a Charachter
    {
        return location;
    }
    string Charachter::print() // prints name,hp,location (look on git)
    {
        string alive = this->getName() + "," + to_string(this->geHitPoints()) + "," + this->getLocation().print();
        string dead = "(" + this->getName() + ")," + this->getLocation().print();

        if (this->isAlive())
            return alive;
        else
            return dead;
    }

    void Charachter::setLocation(Point location)
    {
        this->location = location;
    }

    void Charachter::setIn_Team(bool flag)
    {
        this->in_team = flag;
    }
    
    bool Charachter::getIn_Team()
    {
        return this->in_team;
    }
}