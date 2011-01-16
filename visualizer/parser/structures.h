//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

const int ADD = 0;
const int ATTACK = 1;
const int BUILD = 2;
const int COLLIDE = 3;
const int COMBINE = 4;
const int HEAL = 5;
const int MOVE = 6;
const int REMOVE = 7;
const int SPLIT = 8;
const int TALK = 9;

struct Mappable
{
  int id;
  int x;
  int y;

  friend std::ostream& operator<<(std::ostream& stream, Mappable obj);
};

struct Unit: public Mappable 
{
  int owner;
  int health;
  int maxHealth;
  int size;

  friend std::ostream& operator<<(std::ostream& stream, Unit obj);
};

struct Bot: public Unit 
{
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

  friend std::ostream& operator<<(std::ostream& stream, Bot obj);
};

struct Frame: public Unit 
{
  int type;
  int completionTime;

  friend std::ostream& operator<<(std::ostream& stream, Frame obj);
};

struct Wall: public Unit 
{

  friend std::ostream& operator<<(std::ostream& stream, Wall obj);
};

struct Type
{
  int id;
  char* name;
  int maxHealth;
  int damage;
  int range;
  int movitude;
  int actitude;
  int buildRate;

  friend std::ostream& operator<<(std::ostream& stream, Type obj);
};


struct Animation
{
  int type;
};

struct Add : public Animation
{
  int robot;

  friend std::ostream& operator<<(std::ostream& stream, Add obj);
};

struct Attack : public Animation
{
  int attacker;
  int victim;

  friend std::ostream& operator<<(std::ostream& stream, Attack obj);
};

struct Build : public Animation
{
  int builder;
  int frame;

  friend std::ostream& operator<<(std::ostream& stream, Build obj);
};

struct Collide : public Animation
{
  int attacker;
  int victim;
  char* direction;

  friend std::ostream& operator<<(std::ostream& stream, Collide obj);
};

struct Combine : public Animation
{
  int bot1;
  int bot2;
  int bot3;
  int bot4;

  friend std::ostream& operator<<(std::ostream& stream, Combine obj);
};

struct Heal : public Animation
{
  int healer;
  int victim;

  friend std::ostream& operator<<(std::ostream& stream, Heal obj);
};

struct Move : public Animation
{
  int robot;
  char* direction;

  friend std::ostream& operator<<(std::ostream& stream, Move obj);
};

struct Remove : public Animation
{
  int robot;

  friend std::ostream& operator<<(std::ostream& stream, Remove obj);
};

struct Split : public Animation
{
  int robot;

  friend std::ostream& operator<<(std::ostream& stream, Split obj);
};

struct Talk : public Animation
{
  int speaker;
  char* message;

  friend std::ostream& operator<<(std::ostream& stream, Talk obj);
};


struct GameState
{
  std::map<int,Mappable> mappables;
  std::map<int,Unit> units;
  std::map<int,Bot> bots;
  std::map<int,Frame> frames;
  std::map<int,Wall> walls;
  std::map<int,Type> types;

  int turnNumber;
  int playerID;
  int boardX;
  int boardY;
  int gameNumber;
  int player0Time;
  int player1Time;

  std::vector<Animation*> animations;
  friend std::ostream& operator<<(std::ostream& stream, GameState obj);
};

struct Game
{
  std::vector<GameState> states;
  std::string players[2];
  int winner;
	std::string winReason;

  Game();
};

#endif
