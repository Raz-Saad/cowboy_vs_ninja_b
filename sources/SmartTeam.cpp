#include "SmartTeam.hpp"
#include <stdexcept>
#include <limits.h>
#include <iostream>
using namespace std;

namespace ariel
{
    // constructor ,getting a pointer of a leader of the team
    SmartTeam::SmartTeam(Character *leader) : Team(leader)
    {
    }

    // attacks other team
    void SmartTeam::attack(Team *Enemy_Team)
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

    // the attack logic funcion
    void SmartTeam::Attack_Enemy(Team *Enemy_Team)
    {

        Restart_characters_action(); // sets all actions of characters to false
        Character *enemy_to_attack = Most_Low_HP(Enemy_Team);

        // step 1, checking if our cowboys can kill the enemy with the least hp in this turn
        if ((available_cowboys() * 10) >= enemy_to_attack->geHitPoints())
        {
            for (size_t i = 0; i < get_amount_of_members(); i++)
            {
                if (enemy_to_attack->isAlive() == false)
                {
                    if (Enemy_Team->stillAlive() > 0)
                    {
                        enemy_to_attack = Most_Low_HP(Enemy_Team);
                        if ((available_cowboys() * 10) >= enemy_to_attack->geHitPoints())
                            continue; // if we have eoungh cowboys that can kill the enemy
                                      // in this turn so let them, else go to step 2 in the atack
                        else
                            break;
                    }
                    else
                    {
                        return; // if all the enemies in the team are dead, stop attack
                    }
                }

                if (Cowboy *cowboy = dynamic_cast<Cowboy *>(getGroup()[i]))
                {
                    if (cowboy->isAlive() && (cowboy->getDid_action() == false))
                    {
                        cowboy->setDid_action(true);

                        if (cowboy->hasboolets())
                            cowboy->shoot(enemy_to_attack);
                        else
                            cowboy->reload();
                    }
                }
            }
        }

        // step 2,ninjas in our team will slash enemy if they can, if not move to the closest enemy,
        // if the enemy is a ninja and we can get to him in 1 move we stay
        if (get_amount_of_ninjas() > 0)
        {

            for (size_t i = 0; i < get_amount_of_members(); i++)
            {
                if (Enemy_Team->stillAlive() > 0)
                {
                    if (Ninja *ninja = dynamic_cast<Ninja *>(getGroup()[i]))
                    {

                        if (ninja->isAlive() && (ninja->getDid_action() == false))
                        {

                            enemy_to_attack = Closest_Enemy_To_Character(ninja, Enemy_Team);
                            ninja->setDid_action(true);
                            cout << ninja->getName() << " attacked " << enemy_to_attack->getName() << endl;

                            if (ninja->distance(enemy_to_attack) <= 1)
                            {
                                cout << ninja->getName() << " attacked " << enemy_to_attack->getName() << endl;
                                ninja->slash(enemy_to_attack);
                            }
                            else
                            {
                                // if the enemy is a ninja and our ninja can get to him in this turn,we dont move.
                                // we dont want to allow the enemy ninja to attack our ninja first
                                if (dynamic_cast<Ninja *>(enemy_to_attack))
                                {
                                    if (ninja->distance(enemy_to_attack) > ninja->getSpeed())
                                    {
                                        ninja->move(enemy_to_attack);
                                    }
                                }
                                else
                                {
                                    ninja->move(enemy_to_attack);
                                }
                            }
                        }
                    }
                }
                else
                {
                    return; // if all the enemies in the team are dead, stop attack
                }
            }
        }
        // step 3. the remaining cowboys will attack the closet ninja to
        // our team or the enemy with the least hp
        if (Alive_cowboys())
        {
            if (Enemy_Team->Alive_ninjas())
            { // if the enemy has alive ninjas
                enemy_to_attack = Closest_Enemy_Ninja(Enemy_Team);
                for (size_t i = 0; i < get_amount_of_members(); i++)
                {
                    if (Cowboy *cowboy = dynamic_cast<Cowboy *>(getGroup()[i]))
                    {
                        if (cowboy->isAlive() && (cowboy->getDid_action() == false))
                        {
                            cowboy->setDid_action(true);
                            if (cowboy->hasboolets())
                                cowboy->shoot(enemy_to_attack);
                            else
                                cowboy->reload();
                        }
                    }
                }
            }
            else
            { // attack enemy with the least hp

                enemy_to_attack = Most_Low_HP(Enemy_Team);

                for (size_t i = 0; i < get_amount_of_members(); i++)
                {
                    if (Cowboy *cowboy = dynamic_cast<Cowboy *>(getGroup()[i]))
                    {
                        if (cowboy->isAlive() && (cowboy->getDid_action() == false))
                        {
                            cowboy->setDid_action(true);
                            if (cowboy->hasboolets())
                                cowboy->shoot(enemy_to_attack);
                            else
                                cowboy->reload();
                        }
                    }
                }
            }
        }
    }

    // return the most low hp member in the group
    Character *SmartTeam::Most_Low_HP(Team *other)
    {
        if (other == NULL || other->stillAlive() == 0)
        {
            throw std::invalid_argument("invalid input");
        }

        int min_hp = INT_MAX;
        Character *lowest_hp = NULL;

        for (size_t i = 0; i < other->get_amount_of_members(); i++)
        {
            if ((other->getGroup()[i]->isAlive()) && (other->getGroup()[i]->geHitPoints() < min_hp))
            {
                lowest_hp = other->getGroup()[i];
                min_hp = other->getGroup()[i]->geHitPoints();
            }
        }

        return lowest_hp;
    }

    // return the closest enemy ninja to our team
    Character *SmartTeam::Closest_Enemy_Ninja(Team *other)
    {
        if (other == NULL || other->stillAlive() == 0)
        {
            throw std::invalid_argument("invalid input");
        }

        double temp_distance; // for holding the current ninja distance
        double min_distance = INT_MAX;
        Character *closest_ninja = NULL;

        for (size_t i = 0; i < this->get_amount_of_members(); i++)
        {
            for (size_t j = 0; j < other->get_amount_of_members(); j++)
            {
                if (Ninja *ninja = dynamic_cast<Ninja *>(other->getGroup()[j]))
                {
                    if (ninja->isAlive())
                    {
                        temp_distance = this->getGroup()[i]->distance(ninja);

                        if (temp_distance < min_distance)
                        { // if the distance of this current ninja is lower than the previous ninja, update the closet ninja
                            closest_ninja = ninja;
                            min_distance = temp_distance;
                        }
                    }
                }
            }
        }

        return closest_ninja;
    }

    // return the amount of cowboys that still didnt use their action in the attack turn
    size_t SmartTeam::available_cowboys()
    {
        size_t counter = 0;
        for (size_t i = 0; i < get_amount_of_members(); i++)
        {
            // if a this character is a cowboy and also didnt do an action
            if (Cowboy *cowboy = dynamic_cast<Cowboy *>(getGroup()[i]))
            {
                if ((cowboy->isAlive()) && (cowboy->getDid_action() == false) && (cowboy->hasboolets()))
                    counter++;
            }
        }

        return counter;
    }

    // set did_action var to false for all characters in the team
    void SmartTeam::Restart_characters_action()
    {
        for (size_t i = 0; i < get_amount_of_members(); i++)
        {
            getGroup()[i]->setDid_action(false);
        }
    }

    // return the most close character in other team to a specific character
    Character *SmartTeam::Closest_Enemy_To_Character(Character *character, Team *other)
    {
        double min_distance = INT_MAX;
        int min_hp = INT_MAX;
        Character *closet_ch = NULL;

        if (other == NULL || other->get_amount_of_members() == 0 || other->stillAlive() == 0)
        {
            throw std::invalid_argument("invalid input"); /// to fix the text???????
        }

        for (size_t i = 0; i < other->get_amount_of_members(); i++)
        {
            if (other->getGroup()[i]->isAlive())
            {
                double temp = character->distance(other->getGroup()[i]);

                if (temp <= 1)
                { // if our ninja has few targets that he can attack, we want him to attack the enemey with the less hp
                    if (other->getGroup()[i]->geHitPoints() < min_hp)
                    {
                        min_distance = temp;
                        min_hp = other->getGroup()[i]->geHitPoints();
                        closet_ch = other->getGroup()[i];
                    }
                }
                else if (temp < min_distance)
                { // checking if the memeber is closer to the leader and also if he is alive
                    min_distance = temp;
                    min_hp = other->getGroup()[i]->geHitPoints();
                    closet_ch = other->getGroup()[i];
                }
            }
        }

        return closet_ch;
    }
}