//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef STRUCTURES_H
#define STRUCTURES_H

struct Connection;
struct _Mappable;
struct _Unit;
struct _Bot;
struct _Frame;
struct _Wall;
struct _Type;


struct _Mappable
{
  Connection* _c;
  int id;
  int x;
  int y;
};
struct _Unit
{
  Connection* _c;
  int id;
  int x;
  int y;
  int owner;
  int health;
  int maxHealth;
  int size;
};
struct _Bot
{
  Connection* _c;
  int id;
  int x;
  int y;
  int owner;
  int health;
  int maxHealth;
  int size;
  int actions;
  int steps;
  int damage;
  int range;
  int movitude;
  int actitude;
  int buildRate;
  int partOf;
  int building;
  int type;
};
struct _Frame
{
  Connection* _c;
  int id;
  int x;
  int y;
  int owner;
  int health;
  int maxHealth;
  int size;
  _Type* type;
  int completionTime;
};
struct _Wall
{
  Connection* _c;
  int id;
  int x;
  int y;
  int owner;
  int health;
  int maxHealth;
  int size;
};
struct _Type
{
  Connection* _c;
  int id;
  char* name;
  int maxHealth;
  int damage;
  int range;
  int movitude;
  int actitude;
  int buildRate;
};

#endif
