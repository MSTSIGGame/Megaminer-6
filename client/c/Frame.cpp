// -*-c++-*-

#include "Frame.h"
#include "game.h"

#include "Type.h"

Frame::Frame(_Frame* pointer)
{
    ptr = (void*) pointer;
}

int Frame::id()
{
  return ((_Frame*)ptr)->id;
}

int Frame::x()
{
  return ((_Frame*)ptr)->x;
}

int Frame::y()
{
  return ((_Frame*)ptr)->y;
}

int Frame::owner()
{
  return ((_Frame*)ptr)->owner;
}

int Frame::health()
{
  return ((_Frame*)ptr)->health;
}

int Frame::maxHealth()
{
  return ((_Frame*)ptr)->maxHealth;
}

_Type* Frame::type()
{
  return ((_Frame*)ptr)->type;
}

int Frame::size()
{
  return ((_Frame*)ptr)->size;
}

int Frame::completionTime()
{
  return ((_Frame*)ptr)->completionTime;
}


int Frame::talk(std::string message)
{
  return frameTalk( (_Frame*)ptr, message.c_str());
}



std::ostream& operator<<(std::ostream& stream,Frame ob)
{
  stream << "id: " << ((_Frame*)ob.ptr)->id  <<'\n';
  stream << "x: " << ((_Frame*)ob.ptr)->x  <<'\n';
  stream << "y: " << ((_Frame*)ob.ptr)->y  <<'\n';
  stream << "owner: " << ((_Frame*)ob.ptr)->owner  <<'\n';
  stream << "health: " << ((_Frame*)ob.ptr)->health  <<'\n';
  stream << "size: " << ((_Frame*)ob.ptr)->size  <<'\n';
  stream << "maxHealth: " << ((_Frame*)ob.ptr)->maxHealth  <<'\n';
  stream << "type: " << ((_Frame*)ob.ptr)->type  <<'\n';
  stream << "completionTime: " << ((_Frame*)ob.ptr)->completionTime  <<'\n';
  return stream;
}
