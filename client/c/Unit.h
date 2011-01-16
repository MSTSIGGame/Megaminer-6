// -*-c++-*-

#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <string>
#include "structures.h"

#include "Mappable.h"

///An object that exists on the grid
class Unit : public Mappable {
  public:
  Unit(_Unit* ptr = NULL);

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
  ///The length of one side of this Unit
  int size();

  // Actions
  ///Sends a message to be visualized when this unit is selected
  int talk(std::string message);

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Unit ob);
};

#endif

