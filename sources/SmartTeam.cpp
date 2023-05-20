#include "SmartTeam.hpp"
#include <stdexcept>

using namespace std;

namespace ariel
{
    SmartTeam::SmartTeam(Character *leader) : Team(leader) // constructor ,getting a pointer of a leader of the team
    {
        add(leader);
    }

    void SmartTeam::attack(Team *other) // attacks other team
    {
    }

    void SmartTeam::print()
    {
        
    }

}