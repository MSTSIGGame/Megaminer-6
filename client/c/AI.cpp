#include "AI.h"
#include "util.h"

#include <cstdlib>
#include <ctime>

AI::AI(Connection* conn) : BaseAI(conn) {}

const char* AI::username()
{
  return "Shell AI";
}

const char* AI::password()
{
  return "password";
}

string direction[] = {"l","r","u","d"};

//This function is run once, before your first turn.
void AI::init()
{
  srand ( time(NULL) );
}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  for(int i = 0; i < bots.size(); i++)
  {
    if(bots[i].owner() == playerID())
    {
      bots[i].move(direction[rand()%4]);
    }
    if(bots[i].buildRate())
    {
      bots[i].build(types[rand() % types.size()], bots[i].x() + 1, bots[i].y(), 1);
    }
  }
  return true;
}

//This function is run once, after your last turn.
void AI::end(){}
