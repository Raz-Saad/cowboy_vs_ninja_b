#pragma once
#include "Cowboy.hpp"
#include "OldNinja.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
using namespace std;

namespace ariel
{
    class Team
    {
        Character *group[10] = {NULL}; // a team of ninjas and cowboys
        Character *leader = NULL;
        int amount_of_members = 0;

    public:
        Team(Character *leader);               // constructor ,getting a pointer of a leader of the team
        ~Team();                               // destructor
        void add(Character *character);        // adds a Character to the team
        virtual void attack(Team *Enemy_Team); // attacks other team
        int stillAlive();                      // returns how many members in the gorup are alive
        virtual void print();
        int get_amount_of_members();                         // returns how many members are in the group at the moment
        Character **getGroup();                              // return a pointer to the group
        Character *Closest_To_Leader(Team *other, int flag); // return the closest Character to the leader
        virtual void Attack_Enemy(Team *Enemy_Team);          // attack enemies on the enemy team
        Character *getLeader();                              // return the teams leader
        void setLeader(Character *leader);                   // set a leader
    };
}