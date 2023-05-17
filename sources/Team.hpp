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
        Charachter *group[10] = {NULL}; // a team of ninjas and cowboys
        Charachter *leader = NULL;
        int amount_of_members = 0;

    public:
        Team(Charachter *leader);              // constructor ,getting a pointer of a leader of the team
        virtual ~Team();                       // destructor
        void add(Charachter *charachter);      // adds a Charachter to the team
        virtual void attack(Team *Enemy_Team); // attacks other team
        int stillAlive();                      // returns how many members in the gorup are alive
        virtual string print();
        int get_amount_of_members();                          // returns how many members are in the group at the moment
        Charachter **getGroup();                              // return a pointer to the group
        Charachter *Closest_To_Leader(Team *other, int flag); // return the closest charachter to the leader
        void Attack_Enemy(Team *Enemy_Team);                  // attack enemies on the enemy team
    };
}