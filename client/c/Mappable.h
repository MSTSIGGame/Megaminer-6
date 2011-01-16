// -*-c++-*-

#ifndef MAPPABLE_H
#define MAPPABLE_H

#include <iostream>
#include "structures.h"


///An object that exists on the grid
class Mappable {
  public:
  void* ptr;
  Mappable(_Mappable* ptr = NULL);

  // Accessors
  ///Unique Identifier
  int id();
  ///The X position of the top left corner of this object.  X is horizontal
  int x();
  ///The Y position of the top left corner of this object.  Y is vertical
  int y();

  // Actions

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Mappable ob);
};

#endif

