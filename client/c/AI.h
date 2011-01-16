#ifndef AI_H
#define AI_H

#include "BaseAI.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits.h>
#include "util.h"
using namespace std;

///The class implementing gameplay logic.
class AI: public BaseAI
{
public:
  AI(Connection* c);
  virtual const char* username();
  virtual const char* password();
  virtual void init();
  virtual bool run();
  virtual void end();
  
  void unload(Bot& actor, Unit& target);
  bool inRange(Bot& actor, Unit& target);
  Unit* findNearestTarget(Bot& actor);
  void moveTowardsTarget(Bot& actor, Unit& target);
};

#endif
