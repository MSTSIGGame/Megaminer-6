// -*-c++-*-

#include "Unit.h"
#include "game.h"


Unit::Unit(_Unit* pointer)
{
    ptr = (void*) pointer;
}

int Unit::id()
{
  return ((_Unit*)ptr)->id;
}

int Unit::x()
{
  return ((_Unit*)ptr)->x;
}

int Unit::y()
{
  return ((_Unit*)ptr)->y;
}

int Unit::owner()
{
  return ((_Unit*)ptr)->owner;
}

int Unit::health()
{
  return ((_Unit*)ptr)->health;
}

int Unit::maxHealth()
{
  return ((_Unit*)ptr)->maxHealth;
}

int Unit::size()
{
  return ((_Unit*)ptr)->size;
}

int Unit::talk(std::string message)
{
  return unitTalk( (_Unit*)ptr, message.c_str());
}



std::ostream& operator<<(std::ostream& stream,Unit ob)
{
  stream << "id: " << ((_Unit*)ob.ptr)->id  <<'\n';
  stream << "x: " << ((_Unit*)ob.ptr)->x  <<'\n';
  stream << "y: " << ((_Unit*)ob.ptr)->y  <<'\n';
  stream << "owner: " << ((_Unit*)ob.ptr)->owner  <<'\n';
  stream << "health: " << ((_Unit*)ob.ptr)->health  <<'\n';
  stream << "maxHealth: " << ((_Unit*)ob.ptr)->maxHealth  <<'\n';
  return stream;
}
