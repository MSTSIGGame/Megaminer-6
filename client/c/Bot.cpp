// -*-c++-*-

#include "Bot.h"
#include "game.h"

#include "Unit.h"
#include "Bot.h"
#include "Type.h"

Bot::Bot(_Bot* pointer)
{
    ptr = (void*) pointer;
}

int Bot::id()
{
  return ((_Bot*)ptr)->id;
}

int Bot::x()
{
  return ((_Bot*)ptr)->x;
}

int Bot::y()
{
  return ((_Bot*)ptr)->y;
}

int Bot::owner()
{
  return ((_Bot*)ptr)->owner;
}

int Bot::health()
{
  return ((_Bot*)ptr)->health;
}

int Bot::maxHealth()
{
  return ((_Bot*)ptr)->maxHealth;
}

int Bot::actions()
{
  return ((_Bot*)ptr)->actions;
}

int Bot::steps()
{
  return ((_Bot*)ptr)->steps;
}

int Bot::size()
{
  return ((_Bot*)ptr)->size;
}

int Bot::damage()
{
  return ((_Bot*)ptr)->damage;
}

int Bot::range()
{
  return ((_Bot*)ptr)->range;
}

int Bot::movitude()
{
  return ((_Bot*)ptr)->movitude;
}

int Bot::actitude()
{
  return ((_Bot*)ptr)->actitude;
}

int Bot::buildRate()
{
  return ((_Bot*)ptr)->buildRate;
}

int Bot::partOf()
{
  return ((_Bot*)ptr)->partOf;
}

int Bot::building()
{
  return ((_Bot*)ptr)->building;
}

int Bot::type()
{
  return ((_Bot*)ptr)->type;
}


int Bot::talk(std::string message)
{
  return botTalk( (_Bot*)ptr, message.c_str());
}

int Bot::move(std::string direction)
{
  return botMove( (_Bot*)ptr, direction.c_str());
}

int Bot::attack(Unit& target)
{
  return botAttack( (_Bot*)ptr, (_Unit*) target.ptr);
}

int Bot::heal(Bot& target)
{
  return botHeal( (_Bot*)ptr, (_Bot*) target.ptr);
}

int Bot::build(Type& type, int x, int y, int size)
{
  return botBuild( (_Bot*)ptr, (_Type*) type.ptr, x, y, size);
}

int Bot::combine(Bot& bot2, Bot& bot3, Bot& bot4)
{
  return botCombine( (_Bot*)ptr, (_Bot*) bot2.ptr, (_Bot*) bot3.ptr, (_Bot*) bot4.ptr);
}

int Bot::split()
{
  return botSplit( (_Bot*)ptr);
}


int Bot::maxActions()
{
  return botMaxActions( (_Bot*)ptr);
}

int Bot::maxSteps()
{
  return botMaxSteps( (_Bot*)ptr);
}


std::ostream& operator<<(std::ostream& stream,Bot ob)
{
  stream << "id: " << ((_Bot*)ob.ptr)->id  <<'\n';
  stream << "x: " << ((_Bot*)ob.ptr)->x  <<'\n';
  stream << "y: " << ((_Bot*)ob.ptr)->y  <<'\n';
  stream << "owner: " << ((_Bot*)ob.ptr)->owner  <<'\n';
  stream << "health: " << ((_Bot*)ob.ptr)->health  <<'\n';
  stream << "maxHealth: " << ((_Bot*)ob.ptr)->maxHealth  <<'\n';
  stream << "size: " << ((_Bot*)ob.ptr)->size  <<'\n';
  stream << "actions: " << ((_Bot*)ob.ptr)->actions  <<'\n';
  stream << "steps: " << ((_Bot*)ob.ptr)->steps  <<'\n';
  stream << "damage: " << ((_Bot*)ob.ptr)->damage  <<'\n';
  stream << "range: " << ((_Bot*)ob.ptr)->range  <<'\n';
  stream << "movitude: " << ((_Bot*)ob.ptr)->movitude  <<'\n';
  stream << "actitude: " << ((_Bot*)ob.ptr)->actitude  <<'\n';
  stream << "buildRate: " << ((_Bot*)ob.ptr)->buildRate  <<'\n';
  stream << "partOf: " << ((_Bot*)ob.ptr)->partOf  <<'\n';
  stream << "building: " << ((_Bot*)ob.ptr)->building  <<'\n';
  stream << "type: " << ((_Bot*)ob.ptr)->type  <<'\n';
  return stream;
}
