// -*-c++-*-

#include "Wall.h"
#include "game.h"


Wall::Wall(_Wall* pointer)
{
    ptr = (void*) pointer;
}

int Wall::id()
{
  return ((_Wall*)ptr)->id;
}

int Wall::x()
{
  return ((_Wall*)ptr)->x;
}

int Wall::y()
{
  return ((_Wall*)ptr)->y;
}

int Wall::owner()
{
  return ((_Wall*)ptr)->owner;
}

int Wall::health()
{
  return ((_Wall*)ptr)->health;
}

int Wall::maxHealth()
{
  return ((_Wall*)ptr)->maxHealth;
}

int Wall::size()
{
  return ((_Wall*)ptr)->size;
}

int Wall::talk(std::string message)
{
  return wallTalk( (_Wall*)ptr, message.c_str());
}


std::ostream& operator<<(std::ostream& stream,Wall ob)
{
  stream << "id: " << ((_Wall*)ob.ptr)->id  <<'\n';
  stream << "x: " << ((_Wall*)ob.ptr)->x  <<'\n';
  stream << "y: " << ((_Wall*)ob.ptr)->y  <<'\n';
  stream << "owner: " << ((_Wall*)ob.ptr)->owner  <<'\n';
  stream << "health: " << ((_Wall*)ob.ptr)->health  <<'\n';
  stream << "maxHealth: " << ((_Wall*)ob.ptr)->maxHealth  <<'\n';
  stream << "size: " << ((_Wall*)ob.ptr)->size  <<'\n';
  return stream;
}

