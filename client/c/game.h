//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef GAME_H
#define GAME_H

#include "network.h"
#include "structures.h"

#ifdef _WIN32
#define DLLEXPORT extern "C" __declspec(dllexport)
#include "pthread.h"
#else
#define DLLEXPORT
#include <pthread.h>
#endif

struct Connection
{
  int socket;
  
  #ifndef THREADLESS
  pthread_mutex_t mutex;
  #endif
  
  int turnNumber;
  int playerID;
  int boardX;
  int boardY;
  int gameNumber;
  int player0Time;
  int player1Time;
  char* player0Name;
  char* player1Name;

  _Bot* Bots;
  int BotCount;
  _Frame* Frames;
  int FrameCount;
  _Wall* Walls;
  int WallCount;
  _Type* Types;
  int TypeCount;
};

#ifdef __cplusplus
extern "C"
{
#endif
  DLLEXPORT Connection* createConnection();
  DLLEXPORT int serverConnect(Connection* c, const char* host, const char* port);

  DLLEXPORT int serverLogin(Connection* c, const char* username, const char* password);
  DLLEXPORT int createGame(Connection* c);
  DLLEXPORT int joinGame(Connection* c, int id);

  DLLEXPORT void endTurn(Connection* c);
  DLLEXPORT void getStatus(Connection* c);


//commands

  ///Sends a message to be visualized when this unit is selected
  DLLEXPORT int unitTalk(_Unit* object, const char* message);
  ///Sends a message to be visualized when this unit is selected
  DLLEXPORT int botTalk(_Bot* object, const char* message);
  ///Move in the indicated direction (U, D, L, or R).  U is y=y-1, L=x=x-1, such that the top left corner is (0,0). Requires the calling robot to have a step.
  DLLEXPORT int botMove(_Bot* object, const char* direction);
  ///Attack the specified unit.  Requires the calling robot to have an action and for the target to be in range
  DLLEXPORT int botAttack(_Bot* object, _Unit* target);
  ///Heals the indicated bot.  Requires the calling robot to have an action and for the target to be in range.  Heals for target.maxHealth * self.buildRate / (4 * target.size^2)
  DLLEXPORT int botHeal(_Bot* object, _Bot* target);
  ///Begins building a new robot.  While building, the new robot will be a frame.  Requires the calling robot to have an action. X and Y must cause the new robot to be adjacent.  Size must be less than or equal to the calling robots size.  Completes in 8 * size^2 / self.buildRate turns
  DLLEXPORT int botBuild(_Bot* object, _Type* type, int x, int y, int size);
  ///Combines four robots into one.  Requires all robots to have an action, be of the same size, and be arranged in a square
  DLLEXPORT int botCombine(_Bot* object, _Bot* bot2, _Bot* bot3, _Bot* bot4);
  ///Splits a compound bot into the 4 robots that combined to make it.  Requires the calling robot to have an action.
  DLLEXPORT int botSplit(_Bot* object);
  ///Sends a message to be visualized when this unit is selected
  DLLEXPORT int frameTalk(_Frame* object, const char* message);
  ///Sends a message to be visualized when this unit is selected
  DLLEXPORT int wallTalk(_Wall* object, const char* message);

//derived properties

  ///Returns the maximum number of actions this robot can take per turn.
  DLLEXPORT int botMaxActions(_Bot* object);
  ///Returns the maximum number of steps this robot can take per turn.
  DLLEXPORT int botMaxSteps(_Bot* object);


//accessors

DLLEXPORT int getTurnNumber(Connection* c);
DLLEXPORT int getPlayerID(Connection* c);
DLLEXPORT int getBoardX(Connection* c);
DLLEXPORT int getBoardY(Connection* c);
DLLEXPORT int getGameNumber(Connection* c);
DLLEXPORT int getPlayer0Time(Connection* c);
DLLEXPORT int getPlayer1Time(Connection* c);
DLLEXPORT char* getPlayer0Name(Connection* c);
DLLEXPORT char* getPlayer1Name(Connection* c);

DLLEXPORT _Bot* getBot(Connection* c, int num);
DLLEXPORT int getBotCount(Connection* c);

DLLEXPORT _Frame* getFrame(Connection* c, int num);
DLLEXPORT int getFrameCount(Connection* c);

DLLEXPORT _Wall* getWall(Connection* c, int num);
DLLEXPORT int getWallCount(Connection* c);

DLLEXPORT _Type* getType(Connection* c, int num);
DLLEXPORT int getTypeCount(Connection* c);



  DLLEXPORT int networkLoop(Connection* c);
#ifdef __cplusplus
}
#endif

#endif
