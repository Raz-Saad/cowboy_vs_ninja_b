#include "Team.hpp"
#include <limits.h>
#include <iostream>
#include <stdexcept>

using namespace std;

namespace ariel
{
    Team::Team(Character *leader) // constructor ,getting a pointer of a leader of the team
    {
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

    Team::~Team() // destructor
    {
        for (int i = 0; i < amount_of_members; i++)
        {
            if (group[i] != NULL)
            {
                delete group[i];
                group[i] = NULL;
            }
        }
        leader = NULL;
    }

    void Team::add(Character *character) // adds a Charachter to the team
    {
        if (character->getIn_Team())
        {
            throw std::runtime_error("this charachter is already in a team");
        }
        else
        {
            if (amount_of_members < 10)
            {
                group[amount_of_members++] = character;
                character->setIn_Team(true);
            }
            else
            {
                throw std::runtime_error("can not add more than 10 character to a team");
            }
        }
    }

    void Team::attack(Team *Enemy_Team) // attacks other team
    {
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

    int Team::stillAlive() // returns the amount of live Charachter in the team
    {
        int alive_counter = 0; // counts how many charachters in the team are alive
        if (amount_of_members > 0)
        {
            for (int i = 0; i < amount_of_members; i++)
            {
                if (group[i]->isAlive())
                    alive_counter++;
            }
        }
        else
        {
            throw std::runtime_error("there is no charachter in this team yet");
        }

        return alive_counter;
    }

    void Team::print()
    {
        // First print all the cowboys
        for (int i = 0; i < get_amount_of_members(); i++)
        {
            if (Cowboy *cowboy = dynamic_cast<Cowboy *>(getGroup()[i]))
            {
                cout << cowboy->print() << endl;
            }
        }

        // Seond print all the ninjas
        for (int i = 0; i < get_amount_of_members(); i++)
        {
            if (Ninja *ninja = dynamic_cast<Ninja *>(getGroup()[i]))
            {
                cout << ninja->print() << endl;
            }
        }
    }

    int Team::get_amount_of_members() // returns how many members are in the group at the moment
    {
        return amount_of_members;
    }

    Character **Team::getGroup()
    {
        return group;
    }

    Character *Team::Closest_To_Leader(Team *other, int flag) // flag =1 get new leader , flag=0 find closet enemy
    {
        double min = INT_MAX;
        Character *closet_ch = NULL;
        if (flag)
        {
            if (other == NULL || other->get_amount_of_members() == 1 || other->stillAlive() == 0)
            {
                throw std::invalid_argument("invalid input,TEAM"); /// to fix the text???????
            }

            // the leader will always be at the first cell in the array
            for (int i = 1; i < other->get_amount_of_members(); i++)
            {
                if ((leader->distance(other->getGroup()[i])) < min && (other->getGroup()[i]->isAlive()))
                { // checking if the memeber is closer to the leader and also if he is alive
                    min = leader->distance(other->getGroup()[i]);
                    closet_ch = other->getGroup()[i];
                }
            }
        }
        else
        { // get closet enemy

            if (other == NULL || other->get_amount_of_members() == 0 || other->stillAlive() == 0)
            {
                throw std::invalid_argument("invalid input,TEAM"); /// to fix the text???????
            }

            for (int i = 0; i < other->get_amount_of_members(); i++)
            {
                if ((leader->distance(other->getGroup()[i])) < min && (other->getGroup()[i]->isAlive()))
                { // checking if the memeber is closer to the leader and also if he is alive
                    min = leader->distance(other->getGroup()[i]);
                    closet_ch = other->getGroup()[i];
                }
            }
        }

        return closet_ch;
    }

    void Team::Attack_Enemy(Team *Enemy_Team)
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
        }

        // Seond all the ninjas attack
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


    Character *Team::getLeader()
    {
        return leader;
    }
    void Team::setLeader(Character *leader)
    {
        this->leader=leader;
    }
}