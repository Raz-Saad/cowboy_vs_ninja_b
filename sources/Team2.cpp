#include "Team2.hpp"
#include <stdexcept>

using namespace std;

namespace ariel
{
    Team2::Team2(Charachter *leader) : Team(leader) // constructor ,getting a pointer of a leader of the team
    {
        add(leader);
    }

    Team2::~Team2() // destructor
    {
    }

    void Team2::attack(Team *other) // attacks other team
    {
    }

    string Team2::print()
    {
        return "nothing";
    }

}