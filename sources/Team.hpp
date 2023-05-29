#pragma once
#include <array>
#include "Cowboy.hpp"
#include "OldNinja.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
using namespace std;

const int TEAM_SIZE = 10;
namespace ariel
{
    class Team
    {
        array<Character *, TEAM_SIZE> group; // a team of ninjas and cowboys
        Character *leader = NULL;            // the leader of the team
        size_t amount_of_members = 0;        // amount of memebers in the team
        size_t amount_of_cowboys = 0;        // amount of cowboys in the team
        size_t amount_of_ninjas = 0;         // amount of ninjas in the team

    public:
        Team(Character *leader);               // constructor ,getting a pointer of a leader of the team
        virtual ~Team();                       // destructor
        void add(Character *character);        // adds a character to the team
        virtual void attack(Team *Enemy_Team); // attacks other team
        int stillAlive();                      // returns how many members in the gorup are alive
        virtual void print();
        size_t get_amount_of_members();                      // returns how many members are in the group at the moment
        array<Character *, TEAM_SIZE> &getGroup();           // return a refernce to the group
        Character *Closest_To_Leader(Team *other, int flag); // return the closest character to the leader
        virtual void Attack_Enemy(Team *Enemy_Team);         // the attack logic funcion, first attack with cowboys then with ninjas
        Character *getLeader();                              // return the teams leader
        void setLeader(Character *leader);                   // set a leader
        bool Alive_ninjas();                                 // return true if we have an alive ninja in our team
        bool Alive_cowboys();                                // return true if we have an alive cowboy in our team
        size_t get_amount_of_cowboys();                      // returns how many cowboys are in the group at the moment
        size_t get_amount_of_ninjas();                       // returns how many ninjas are in the group at the moment

        // constructors that I use becuase of tidy
        Team(const Team &) = delete;            // Copy constructor
        Team &operator=(const Team &) = delete; // Copy assignment operator
        Team(Team &&) = delete;                 // Move constructor
        Team &operator=(Team &&) = delete;      // Move assignment operator
    };
}