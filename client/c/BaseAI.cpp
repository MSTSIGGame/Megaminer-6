//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that

#include "BaseAI.h"
#include "game.h"

int BaseAI::turnNumber()
{
  return getTurnNumber(c);
}
int BaseAI::playerID()
{
  return getPlayerID(c);
}
int BaseAI::boardX()
{
  return getBoardX(c);
}
int BaseAI::boardY()
{
  return getBoardY(c);
}
int BaseAI::gameNumber()
{
  return getGameNumber(c);
}
int BaseAI::player0Time()
{
  return getPlayer0Time(c);
}
int BaseAI::player1Time()
{
  return getPlayer1Time(c);
}
char* BaseAI::player0Name()
{
  return getPlayer0Name(c);
}
char* BaseAI::player1Name()
{
  return getPlayer1Name(c);
}

bool BaseAI::startTurn()
{
  static bool initialized = false;
  int count = 0;
  count = getBotCount(c);
  bots.clear();
  bots.resize(count);
  for(int i = 0; i < count; i++)
  {
    bots[i] = Bot(getBot(c, i));
  }

  count = getFrameCount(c);
  frames.clear();
  frames.resize(count);
  for(int i = 0; i < count; i++)
  {
    frames[i] = Frame(getFrame(c, i));
  }

  count = getWallCount(c);
  walls.clear();
  walls.resize(count);
  for(int i = 0; i < count; i++)
  {
    walls[i] = Wall(getWall(c, i));
  }

  count = getTypeCount(c);
  types.clear();
  types.resize(count);
  for(int i = 0; i < count; i++)
  {
    types[i] = Type(getType(c, i));
  }

  if(!initialized)
  {
    initialized = true;
    init();
  }
  return run();
}

BaseAI::BaseAI(Connection* conn) : c(conn) {}
BaseAI::~BaseAI() {}
