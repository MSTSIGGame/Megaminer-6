// -*-c++-*-

#ifndef FRAME_H
#define FRAME_H

#include <iostream>
#include <string>
#include "structures.h"

#include "Unit.h"
class Type;

///A baby robot.
class Frame : public Unit {
  public:
  Frame(_Frame* ptr = NULL);

  // Accessors
  ///Unique Identifier
  int id();
  ///The X position of the top left corner of this object.  X is horizontal
  int x();
  ///The Y position of the top left corner of this object.  Y is vertical
  int y();
  ///The owning player
  int owner();
  ///How much health this unit currently has
  int health();
  ///The maximum amount of health this unit can ever have
  int maxHealth();
  ///What type this robot will be
  _Type* type();
  ///The length of one side of this robot, such that size^2 = number of bots combined into this bot
  int size();
  ///How many of your turns until this frame becomes a robot
  int completionTime();

  // Actions
  ///Sends a message to be visualized when this unit is selected
  int talk(std::string message);

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Frame ob);
};

#endif

