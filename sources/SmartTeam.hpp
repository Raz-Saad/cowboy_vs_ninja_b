#pragma once
#include "Team.hpp"
using namespace std;

namespace ariel
{
    class SmartTeam : public Team
    {

    public:
        SmartTeam(Character *leader);                                             // constructor ,getting a pointer of a leader of the team
        void attack(Team *Enemy_Team) override;                                   // attacks other team
        void Attack_Enemy(Team *Enemy_Team) override;                             // the attack logic funcion
        size_t available_cowboys();                                               // return the amount of cowboys that still didnt use their action and can shoot in the attack turn
        Character *Most_Low_HP(Team *other);                                      // return the most low hp member in the group
        Character *Closest_Enemy_Ninja(Team *other);                              // return the closest enemy ninja to our team
        void Restart_characters_action();                                         // set did_action var to false for all characters in the team
        Character *Closest_Enemy_To_Character(Character *character, Team *other); // return the most close character in other team to a specific character
    };
}