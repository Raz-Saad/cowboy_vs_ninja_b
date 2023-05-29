#include "Team.hpp"
#include <limits.h>
#include <iostream>
#include <stdexcept>

using namespace std;

namespace ariel
{
    // constructor ,getting a pointer of a leader of the team
    Team::Team(Character *leader)
    {
        group.fill(nullptr); // initialize array with null
        if (leader->getIn_Team())
        {
            throw std::runtime_error("this charachter is already in a team");
        }
        else
        {
            this->leader = leader;
            add(leader);
        }
    }

    // destructor
    Team::~Team()
    {
        for (size_t i = 0; i < amount_of_members; i++)
        {
            if (group[i] != nullptr)
            {
                group[i]->setIn_Team(false);
                delete group[i];
                group[i] = nullptr;
            }
        }
        leader = NULL;
    }

    // adds a character to the team
    void Team::add(Character *character)
    {

        if (amount_of_members < 10)
        {
            if (character->getIn_Team())
            {
                throw std::runtime_error("this charachter is already in a team");
            }
            else
            {
                character->setIn_Team(true);
                group[amount_of_members++] = character;

                if (dynamic_cast<Ninja *>(character))
                    amount_of_ninjas++;
                else if (dynamic_cast<Cowboy *>(character))
                    amount_of_cowboys++;
            }
        }
        else
        {
            throw std::runtime_error("can not add more than 10 character to a team");
        }
    }

    // attacks other team
    void Team::attack(Team *Enemy_Team)
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
            if (leader->isAlive() == false)
            { // setting a new leader to the team and attack
                leader = Closest_To_Leader(this, 1);
                Attack_Enemy(Enemy_Team);
            }
            else
            {
                // attack the enemy team
                Attack_Enemy(Enemy_Team);
            }
        }
    }

    // returns how many members in the gorup are alive
    int Team::stillAlive()
    {
        int alive_counter = 0; // counts how many charachters in the team are alive
        if (amount_of_members > 0)
        {
            for (size_t i = 0; i < amount_of_members; i++)
            {
                if (group[i]->isAlive())
                    alive_counter++;
            }
        }

        return alive_counter;
    }

    void Team::print()
    {
        // First print all the cowboys
        for (size_t i = 0; i < get_amount_of_members(); i++)
        {
            if (Cowboy *cowboy = dynamic_cast<Cowboy *>(getGroup()[i]))
            {
                cout << cowboy->print() << endl;
            }
        }

        // Seond print all the ninjas
        for (size_t i = 0; i < get_amount_of_members(); i++)
        {
            if (Ninja *ninja = dynamic_cast<Ninja *>(getGroup()[i]))
            {
                cout << ninja->print() << endl;
            }
        }
    }

    // returns how many members are in the group at the moment
    size_t Team::get_amount_of_members()
    {
        return amount_of_members;
    }

    // return a refernce to the group
    array<Character *, TEAM_SIZE> &Team::getGroup()
    {
        return group;
    }

    // return the closest character to the leader. flag =1 get new leader , flag=0 find closet enemy to our leader
    Character *Team::Closest_To_Leader(Team *other, int flag)
    {
        double min = INT_MAX;
        Character *closet_ch = NULL;
        if (flag)
        { // find a new leader to our team

            if (other == NULL || other->get_amount_of_members() == 1 || other->stillAlive() == 0)
            {
                throw std::invalid_argument("invalid input, in change leader function"); /// to fix the text???????
            }

            // the leader will always be at the first cell in the array
            for (size_t i = 1; i < other->get_amount_of_members(); i++)
            {
                if ((leader->distance(other->getGroup()[i])) < min && (other->getGroup()[i]->isAlive()))
                { // checking if the memeber is closer to the leader and also if he is alive
                    min = leader->distance(other->getGroup()[i]);
                    closet_ch = other->getGroup()[i];
                }
            }
        }
        else
        { // get closet enemy to our leader

            if (other == NULL || other->get_amount_of_members() == 0 || other->stillAlive() == 0)
            {
                throw std::invalid_argument("invalid input,TEAM"); /// to fix the text???????
            }

            for (size_t i = 0; i < other->get_amount_of_members(); i++)
            {
                if ((other->getGroup()[i]->isAlive()) && (leader->distance(other->getGroup()[i])) < min)
                { // checking if the memeber is closer to the leader and also if he is alive
                    min = leader->distance(other->getGroup()[i]);
                    closet_ch = other->getGroup()[i];
                }
            }
        }

        return closet_ch;
    }

    // the attack logic funcion, first attack with cowboys then with ninjas
    void Team::Attack_Enemy(Team *Enemy_Team)
    {
        Character *enemy_to_attack = Closest_To_Leader(Enemy_Team, 0); // get the closet enemy to our leader

        // First all the cowboys attack
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
        }

        // Seond all the ninjas attack
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

            if (Ninja *ninja = dynamic_cast<Ninja *>(getGroup()[i]))
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

    // return the teams leader
    Character *Team::getLeader()
    {
        return leader;
    }

    // set a leader
    void Team::setLeader(Character *leader)
    {
        this->leader = leader;
    }

    // returns how many ninjas are in the group at the moment
    bool Team::Alive_ninjas()
    {
        if (stillAlive() > 0)
        {
            for (size_t i = 0; i < get_amount_of_members(); i++)
            {
                if ((dynamic_cast<Ninja *>(getGroup()[i])) && (getGroup()[i]->isAlive()))
                {
                    return true;
                }
            }
        }
        else
        {
            return false;
        }

        return false;
    }

    // return true if we have an alive cowboy in our team
    bool Team::Alive_cowboys()
    {
        if (stillAlive() > 0)
        {
            for (size_t i = 0; i < get_amount_of_members(); i++)
            {
                if ((dynamic_cast<Cowboy *>(getGroup()[i])) && (getGroup()[i]->isAlive()))
                {
                    return true;
                }
            }
        }
        else
        {
            return false;
        }

        return false;
    }

    // returns how many cowboys are in the group at the moment
    size_t Team::get_amount_of_cowboys()
    {
        return amount_of_cowboys;
    }

    // returns how many ninjas are in the group at the moment
    size_t Team::get_amount_of_ninjas()
    {
        return amount_of_ninjas;
    }

}