#include "Team2.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

namespace ariel
{
    // constructor ,getting a pointer of a leader of the team
    Team2::Team2(Character *leader) : Team(leader)
    {
    }

    // the attack function, calls a help function attack_enemy function inorder to attack
    void Team2::attack(Team *Enemy_Team)
    {
        if (Enemy_Team == NULL)
        {
            throw std::invalid_argument("invalid team pointer, NULL");
        }

        if (this->stillAlive() == 0 || Enemy_Team->stillAlive() == 0)
        {
            throw std::runtime_error("can not attack all the members in the group are dead");
        }
        else
        {
            if (getLeader()->isAlive() == false)
            { // setting a new leader to the team and attack
                setLeader(Closest_To_Leader(this, 1));
                Attack_Enemy(Enemy_Team);
            }
            else
            {
                // attack the enemy team
                Attack_Enemy(Enemy_Team);
            }
        }
    }

    void Team2::print()
    {
        // prints according to the queue in the group
        for (size_t i = 0; i < get_amount_of_members(); i++)
        {
            if (Cowboy *cowboy = dynamic_cast<Cowboy *>(getGroup()[i]))
            {
                cout << cowboy->print() << endl;
            }
            else if (Ninja *ninja = dynamic_cast<Ninja *>(getGroup()[i]))
            {
                cout << ninja->print() << endl;
            }
        }
    }

    // the attack logic funcion, attacks according to the order of the characters in the team
    void Team2::Attack_Enemy(Team *Enemy_Team)
    {
        Character *enemy_to_attack = Closest_To_Leader(Enemy_Team, 0); // get the closet enemy to our leader

        // attacking according to the queue in the group
        for (size_t i = 0; i < get_amount_of_members(); i++)
        {
            // checking if the enemy is alive if not change target
            if (enemy_to_attack->isAlive() == false)
            {
                if (Enemy_Team->stillAlive() > 0)
                {
                    enemy_to_attack = Closest_To_Leader(Enemy_Team, 0);
                }
                else
                {
                    return; // if all the enemies in the team are dead, stop attack
                }
            }

            if (Cowboy *cowboy = dynamic_cast<Cowboy *>(getGroup()[i]))
            {
                if (cowboy->isAlive())
                {
                    if (cowboy->hasboolets())
                        cowboy->shoot(enemy_to_attack);
                    else
                        cowboy->reload();
                }
            }
            else if (Ninja *ninja = dynamic_cast<Ninja *>(getGroup()[i]))
            {
                if (ninja->isAlive())
                {
                    if (ninja->distance(enemy_to_attack) <= 1)
                        ninja->slash(enemy_to_attack);
                    else
                        ninja->move(enemy_to_attack);
                }
            }
        }
    }

}