// -*-c++-*-

#include "Type.h"
#include "game.h"


Type::Type(_Type* pointer)
{
    ptr = (void*) pointer;
}

int Type::id()
{
  return ((_Type*)ptr)->id;
}

char* Type::name()
{
  return ((_Type*)ptr)->name;
}

int Type::maxHealth()
{
  return ((_Type*)ptr)->maxHealth;
}

int Type::damage()
{
  return ((_Type*)ptr)->damage;
}

int Type::range()
{
  return ((_Type*)ptr)->range;
}

int Type::movitude()
{
  return ((_Type*)ptr)->movitude;
}

int Type::actitude()
{
  return ((_Type*)ptr)->actitude;
}

int Type::buildRate()
{
  return ((_Type*)ptr)->buildRate;
}




std::ostream& operator<<(std::ostream& stream,Type ob)
{
  stream << "id: " << ((_Type*)ob.ptr)->id  <<'\n';
  stream << "name: " << ((_Type*)ob.ptr)->name  <<'\n';
  stream << "maxHealth: " << ((_Type*)ob.ptr)->maxHealth  <<'\n';
  stream << "damage: " << ((_Type*)ob.ptr)->damage  <<'\n';
  stream << "range: " << ((_Type*)ob.ptr)->range  <<'\n';
  stream << "movitude: " << ((_Type*)ob.ptr)->movitude  <<'\n';
  stream << "actitude: " << ((_Type*)ob.ptr)->actitude  <<'\n';
  stream << "buildRate: " << ((_Type*)ob.ptr)->buildRate  <<'\n';
  return stream;
}
