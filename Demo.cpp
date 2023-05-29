/**
 * Demo file for the exercise on binary tree
 *
 * @author Evgeny Hershkovitch Neiterman
 * @since 2023-03
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>
using namespace std;

#include "sources/Team.hpp" //no need for other includes
#include "sources/Team2.hpp"
#include "sources/SmartTeam.hpp"

using namespace ariel;

int main()
{
   cout << "==============================" << endl;

   cout << "          original demo" << endl;
   cout << "==============================" << endl;

   Point a(32.3, 44), b(1.3, 3.5);
   assert(a.distance(b) == b.distance(a));
   Cowboy *tom = new Cowboy("Tom", a);
   OldNinja *sushi = new OldNinja("sushi", b);
   tom->shoot(sushi);
   cout << tom->print() << endl;

   sushi->move(tom);
   cout << sushi->getLocation().print() << endl;
   // sushi->slash(tom);

   Team team_A(tom);
   team_A.add(new YoungNinja("Yogi", Point(64, 57)));
   // Team b(tom); should throw tom is already in team a

   Team team_B(sushi);
   team_B.add(new TrainedNinja("Hikari", Point(12, 81)));

   while (team_A.stillAlive() > 0 && team_B.stillAlive() > 0)
   {
      team_A.attack(&team_B);
      team_B.attack(&team_A);
      team_A.print();
      team_B.print();
   }

   if (team_A.stillAlive() > 0)
      cout << "winner is team_A" << endl;
   else
      cout << "winner is team_B" << endl;

   cout << "==============================" << endl;

   cout << "          my demo" << endl;
   cout << "==============================" << endl;

   //---------------------------------

   cout << "Team2 Vs Team" << endl
        << endl;

   Cowboy *raz = new Cowboy("Raz", a);
   OldNinja *maor = new OldNinja("Maor", b);

   Team2 team2(raz);
   team2.add(new YoungNinja("Young_S", Point(64, 57)));
   team2.add(new TrainedNinja("Trained_S", Point(5, 100)));
   team2.add(new OldNinja("Old_S", Point(6.7, 22)));
   team2.add(new Cowboy("Cowboy_S", Point(22, 3.5)));

   Team team(maor);
   team.add(new TrainedNinja("Trained_N", Point(12, 81)));
   team.add(new Cowboy("Cowboy_N1", Point(10, 10)));
   team.add(new OldNinja("Old_N", Point(50, 70)));
   team.add(new Cowboy("Cowboy_N2", Point(82, 11)));

   cout << "Team2 A:" << endl;
   team2.print();
   cout << "Team B:" << endl;
   team.print();
   cout << endl;
   int i = 1;
   while (team2.stillAlive() > 0 && team.stillAlive() > 0)
   {
      try
      {
         cout << "Round " << i << endl;
         team2.attack(&team);
         team.attack(&team2);

         cout << "Team A:" << endl;
         team2.print();
         cout << "Team B:" << endl;
         team.print();
         cout << endl;
         i++;
      }
      catch (...)
      {
         continue;
      }
   }

   if (team2.stillAlive() > 0)
      cout << "winner is Team2" << endl;
   else
      cout << "winner is Team" << endl;

   //---------------------------------
   cout << endl;
   cout << "SmartTeam Vs Team (1 TrainedNinja vs 1 TrainedNinja)" << endl
        << endl;

   TrainedNinja *raz1 = new TrainedNinja("Raz", a);
   TrainedNinja *Julia = new TrainedNinja("Julia", b);

   SmartTeam Smart_Ninja_Team(Julia);
   Team Normal_Ninja_Team(raz1);
 
   cout << "Normal_Ninja_Team:" << endl;
   Smart_Ninja_Team.print();
   cout << "Smart_Ninja_Team:" << endl;
   Normal_Ninja_Team.print();
   cout << endl;

   i = 1;
   while (Smart_Ninja_Team.stillAlive() > 0 && Normal_Ninja_Team.stillAlive() > 0)
   {
      try
      {
         cout << "Round " << i << endl;
         Normal_Ninja_Team.attack(&Smart_Ninja_Team);
         Smart_Ninja_Team.attack(&Normal_Ninja_Team);

         cout << "Normal_Ninja_Team:" << endl;
         Normal_Ninja_Team.print();
         cout << "Smart_Ninja_Team:" << endl;
         Smart_Ninja_Team.print();
         cout << endl;
         i++;
      }
      catch (...)
      {
         continue;
      }
   }

   if (Smart_Ninja_Team.stillAlive() > 0)
      cout << "winner is Smart_Ninja_Team" << endl;
   else
      cout << "winner is Normal_Ninja_Team" << endl;

   //---------------------------------
   cout << endl;
   cout << "Team Vs SmartTeam (5 vs 5)" << endl
        << endl;

   TrainedNinja *Bob = new TrainedNinja("Bob", a);
   TrainedNinja *Alice = new TrainedNinja("Alice", b);

   Team Team_Group(Bob);
   Team_Group.add(new YoungNinja("Young_N", Point(64, 57)));
   Team_Group.add(new TrainedNinja("Trained_N", Point(5, 100)));
   Team_Group.add(new OldNinja("Old_N", Point(6.7, 22)));
   Team_Group.add(new Cowboy("Cowboy_N", Point(22, 3.5)));

   SmartTeam Smart_Group(Alice);
   Smart_Group.add(new TrainedNinja("Trained_S", Point(12, 81)));
   Smart_Group.add(new Cowboy("Cowboy_S1", Point(10, 10)));
   Smart_Group.add(new OldNinja("Old_S", Point(50, 70)));
   Smart_Group.add(new Cowboy("Cowboy_S2", Point(82, 11)));

   cout << "Normal Team:" << endl;
   Team_Group.print();
   cout << "Smart Team:" << endl;
   Smart_Group.print();
   cout << endl;

   i = 1;
   while (Team_Group.stillAlive() > 0 && Smart_Group.stillAlive() > 0)
   {
      try
      {
         cout << "Round " << i << endl;
         Team_Group.attack(&Smart_Group);
         Smart_Group.attack(&Team_Group);

         cout << "Normal Team:" << endl;
         Team_Group.print();
         cout << "Smart Team:" << endl;
         Smart_Group.print();
         cout << endl;
         i++;
      }
      catch (...)
      {
         continue;
      }
   }

   if (Smart_Group.stillAlive() > 0)
      cout << "winner is Smart Team" << endl;
   else
      cout << "winner is Normal Team" << endl;

   return 0; // no memory issues. Team should free the memory of its members. both a and b teams are on the stack.
}