// -*-c++-*-

#ifndef BOT_H
#define BOT_H

#include <iostream>
#include <string>
#include "structures.h"

#include "Unit.h"
class Unit;
class Bot;
class Type;

///The bot class.
class Bot : public Unit {
  public:
  Bot(_Bot* ptr = NULL);

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
  ///How many actions this bot can still perform
  int actions();
  ///How many steps this bot can still take
  int steps();
  ///The length of one side of this robot, such that size^2 = number of bots combined into this bot
  int size();
  ///The amount of damage this robot does when attacking
  int damage();
  ///How far this robot can attack or heal from its edge
  int range();
  ///This value divided by the number of bots = maxSteps for this robot
  int movitude();
  ///This value divided by the number of bots = maxActions for this robot
  int actitude();
  ///This value is used to determine how many turns it takes to build a robot and how much this robot heals for
  int buildRate();
  ///ID of the robot this robot is apart of, 0 if not in a robot
  int partOf();
  ///ID of the robot this robot is building, 0 if not building
  int building();
  ///ID of the type this robot is, 0 if a combination
  int type();

  // Actions
  ///Sends a message to be visualized when this unit is selected
  int talk(std::string message);
  ///Move in the indicated direction (U, D, L, or R).  U is y=y-1, L=x=x-1, such that the top left corner is (0,0). Requires the calling robot to have a step.
  int move(std::string direction);
  ///Attack the specified unit.  Requires the calling robot to have an action and for the target to be in range
  int attack(Unit& target);
  ///Heals the indicated bot.  Requires the calling robot to have an action and for the target to be in range.  Heals for target.maxHealth * self.buildRate / (4 * target.size^2)
  int heal(Bot& target);
  ///Begins building a new robot.  While building, the new robot will be a frame.  Requires the calling robot to have an action. X and Y must cause the new robot to be adjacent.  Size must be less than or equal to the calling robots size.  Completes in 8 * size^2 / self.buildRate turns
  int build(Type& type, int x, int y, int size);
  ///Combines four robots into one.  Requires all robots to have an action, be of the same size, and be arranged in a square
  int combine(Bot& bot2, Bot& bot3, Bot& bot4);
  ///Splits a compound bot into the 4 robots that combined to make it.  Requires the calling robot to have an action.
  int split();

  // Properties
  ///Returns the maximum number of actions this robot can take per turn.
  int maxActions();
  ///Returns the maximum number of steps this robot can take per turn.
  int maxSteps();


  friend std::ostream& operator<<(std::ostream& stream, Bot ob);
};

#endif

