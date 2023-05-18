#include "Team2.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

namespace ariel
{
    Team2::Team2(Character *leader) : Team(leader) // constructor ,getting a pointer of a leader of the team
    {
        add(leader);
    }

    // Team2::~Team2() // destructor
    // {
    // }

    void Team2::attack(Team *Enemy_Team) // attacks other team
    {
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
        // First print all the cowboys
        for (int i = 0; i < get_amount_of_members(); i++)
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

    void Team2::Attack_Enemy(Team *Enemy_Team)
    {
        Character *enemy_to_attack = Closest_To_Leader(Enemy_Team, 0); // get the closet enemy to our leader

        // First all the cowboys attack
        for (int i = 0; i < get_amount_of_members(); i++)
        {
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