// -*-c++-*-

#ifndef TYPE_H
#define TYPE_H

#include <iostream>
#include "structures.h"


///A kind of robot.
class Type {
  public:
  void* ptr;
  Type(_Type* ptr = NULL);

  // Accessors
  ///Unique Identifier
  int id();
  ///The name of this type of robot
  char* name();
  ///The maximum amount of health for this type of robot
  int maxHealth();
  ///The amount of damage this type of robot does when attacking
  int damage();
  ///How far this type of robot can attack or heal from its edge
  int range();
  ///This value divided by the number of bots = maxSteps for this type of robot
  int movitude();
  ///This value divided by the number of bots = maxActions for this type of robot
  int actitude();
  ///This value is used to determine how many turns it takes to build a robot and how much this type of robot heals for
  int buildRate();

  // Actions

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Type ob);
};

#endif

