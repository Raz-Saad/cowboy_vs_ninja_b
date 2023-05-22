#pragma once
#include "Team.hpp"
using namespace std;

namespace ariel
{
    class Team2 : public Team
    {

    public:
        Team2(Character *leader);               // constructor ,getting a pointer of a leader of the team
        void attack(Team *Enemy_Team) override; // the attack function, calls a help function attack_enemy function inorder to attack
        void print() override;
        void Attack_Enemy(Team *Enemy_Team) override; // the attack logic funcion, attacks according to the order of the characters in the team
    };
}