#pragma once
#include "Team.hpp"
using namespace std;

namespace ariel
{
    class SmartTeam : public Team
    {

    public:
        SmartTeam(Charachter *leader); // constructor ,getting a pointer of a leader of the team
        ~SmartTeam();                  // destructor
        void attack(Team *other);      // attacks other team
        string print();
    };
}