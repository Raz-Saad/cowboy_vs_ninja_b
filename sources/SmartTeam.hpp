#pragma once
#include "Team.hpp"
using namespace std;

namespace ariel
{
    class SmartTeam : public Team
    {

    public:
        SmartTeam(Character *leader); // constructor ,getting a pointer of a leader of the team
        void attack(Team *other) override;      // attacks other team
        void print() override;
    };
}