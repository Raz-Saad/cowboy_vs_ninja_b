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

   Team2 N2_team_A(raz);
   N2_team_A.add(new YoungNinja("Young_S", Point(64, 57)));
   N2_team_A.add(new TrainedNinja("Trained_S", Point(5, 100)));
   N2_team_A.add(new OldNinja("Old_S", Point(6.7, 22)));
   N2_team_A.add(new Cowboy("Cowboy_S", Point(22, 3.5)));

   Team N_team_B(maor);
   N_team_B.add(new TrainedNinja("Trained_N", Point(12, 81)));
   N_team_B.add(new Cowboy("Cowboy_N1", Point(10, 10)));
   N_team_B.add(new OldNinja("Old_N", Point(50, 70)));
   N_team_B.add(new Cowboy("Cowboy_N2", Point(82, 11)));

   cout << "Team2 A:" << endl;
   N2_team_A.print();
   cout << "Team B:" << endl;
   N_team_B.print();
   cout << endl;
   int i = 1;
   while (N2_team_A.stillAlive() > 0 && N_team_B.stillAlive() > 0)
   {
      try
      {
         cout << "Round " << i << endl;
         N2_team_A.attack(&N_team_B);
         N_team_B.attack(&N2_team_A);

         cout << "Team A:" << endl;
         N2_team_A.print();
         cout << "Team B:" << endl;
         N_team_B.print();
         cout << endl;
         i++;
      }
      catch (...)
      {
         continue;
      }
   }

   if (N2_team_A.stillAlive() > 0)
      cout << "winner is n2_team_A" << endl;
   else
      cout << "winner is N_team_B" << endl;

   //---------------------------------

   cout << "SmartTeam Vs Team2" << endl
        << endl;



   Cowboy *raz1 = new Cowboy("Raz", a);
   OldNinja *maor1 = new OldNinja("Maor", b);

   SmartTeam S_team_A(raz1);
   S_team_A.add(new YoungNinja("Young_S", Point(64, 57)));
   S_team_A.add(new TrainedNinja("Trained_S", Point(5, 100)));
   S_team_A.add(new OldNinja("Old_S", Point(6.7, 22)));
   S_team_A.add(new Cowboy("Cowboy_S", Point(22, 3.5)));

   Team N_team_B1(maor1);
   N_team_B1.add(new TrainedNinja("Trained_N", Point(12, 81)));
   N_team_B1.add(new Cowboy("Cowboy_N1", Point(10, 10)));
   N_team_B1.add(new OldNinja("Old_N", Point(50, 70)));
   N_team_B1.add(new Cowboy("Cowboy_N2", Point(82, 11)));

   cout << "Team2 A:" << endl;
   N2_team_A.print();
   cout << "Team B:" << endl;
   N_team_B1.print();
   cout << endl;

   i = 1;
   while (S_team_A.stillAlive() > 0 && N_team_B1.stillAlive() > 0)
   {
      try
      {
         cout << "Round " << i << endl;
         S_team_A.attack(&N_team_B1);
         N_team_B1.attack(&S_team_A);

         cout << "Team A:" << endl;
         S_team_A.print();
         cout << "Team B:" << endl;
         N_team_B1.print();
         cout << endl;
         i++;
      }
      catch (...)
      {
         continue;
      }
   }

   if (S_team_A.stillAlive() > 0)
      cout << "winner is S_team_A" << endl;
   else
      cout << "winner is N_team_B" << endl;

   return 0; // no memory issues. Team should free the memory of its members. both a and b teams are on the stack.
}
