#pragma once
#include "Point.hpp"
#include <string>
using namespace std;

namespace ariel
{
    class Character
    {
        Point location;
        int HitPoints;
        string name;
        bool in_team;

    public:
        Character();                                           // empty constructor
        virtual ~Character() = default;                        // destructor
        Character(string name, Point location, int HitPoints); // constructor
        bool isAlive();                                        // return true if hitpoint > 0
        double distance(Character *other);                     // return the distance bettwen the Characters
        void hit(int amount);                                  // substract amount from hitpoints
        string getName();                                      // return the name of the Character
        int geHitPoints();                                     // return the hp of a Character
        Point getLocation();                                   // return the location of a Character
        void setLocation(Point location);                      // set a location to the Character
        void setIn_Team(bool flag);                            // set if a Character is in a team or not
        bool getIn_Team();                                     // get if a Character is in a team or not
        virtual string print();                                // prints name,hp,location

        // constructors that I use becuase of tidy
        Character(const Character &) = delete;            // Copy constructor
        Character &operator=(const Character &) = delete; // Copy assignment operator
        Character(Character &&) = delete;                 // Move constructor
        Character &operator=(Character &&) = delete;      // Move assignment operator
    };

}