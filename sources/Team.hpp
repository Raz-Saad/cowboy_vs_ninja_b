#pragma once
#include <array>
#include "Cowboy.hpp"
#include "OldNinja.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
using namespace std;

const int TEAM_SIZE = 10;
namespace ariel
{
    class Team
    {
        array<Character *, TEAM_SIZE> group; // a team of ninjas and cowboys
        Character *leader = NULL;            // the leader of the team
        size_t amount_of_members = 0;        // amount of memebers in the team
        bool is_Ninja_in_Team = false;       // true if there is a ninja in our team

    public:
        Team(Character *leader);               // constructor ,getting a pointer of a leader of the team
        virtual ~Team();                       // destructor
        void add(Character *character);        // adds a Character to the team
        virtual void attack(Team *Enemy_Team); // attacks other team
        int stillAlive();                      // returns how many members in the gorup are alive
        virtual void print();
        int get_amount_of_members();                         // returns how many members are in the group at the moment
        array<Character *, TEAM_SIZE> &getGroup();           // return a refernce to the group
        Character *Closest_To_Leader(Team *other, int flag); // return the closest Character to the leader
        virtual void Attack_Enemy(Team *Enemy_Team);         // attack enemies on the enemy team
        Character *getLeader();                              // return the teams leader
        void setLeader(Character *leader);                   // set a leader

        // functions for SmartTeam
        bool getIs_Ninja();                          // retrun if there is a ninja in our team
        Character *Most_Low_HP(Team *other);         // return the most low hp member in the group
        Character *Closest_Enemy_Ninja(Team *other); // return the Closest enemy ninja to our team

        // constructors that I use becuase of tidy
        Team(const Team &) = delete;            // Copy constructor
        Team &operator=(const Team &) = delete; // Copy assignment operator
        Team(Team &&) = delete;                 // Move constructor
        Team &operator=(Team &&) = delete;      // Move assignment operator
    };
}