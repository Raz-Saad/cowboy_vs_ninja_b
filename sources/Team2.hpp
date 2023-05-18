#pragma once
#include "Team.hpp"
using namespace std;

namespace ariel
{
    class Team2 : public Team
    {

    public:
        Team2(Character *leader); // constructor ,getting a pointer of a leader of the team
        // ~Team2();                  // destructor
        void attack(Team *Enemy_Team);  // attacks other team
        void print();
        void Attack_Enemy(Team *Enemy_Team);
    };
}