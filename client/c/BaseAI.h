//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef BASEAI_H
#define BASEAI_H

#include <vector>
#include <ctime>
#include "game.h"

#include "Mappable.h"
#include "Unit.h"
#include "Bot.h"
#include "Frame.h"
#include "Wall.h"
#include "Type.h"

/// \brief A basic AI interface.

///This class implements most the code an AI would need to interface with the lower-level game code.
///AIs should extend this class to get a lot of boiler-plate code out of the way
///The provided AI class does just that.
class BaseAI
{
protected:
  Connection* c;
  std::vector<Bot> bots;
  std::vector<Frame> frames;
  std::vector<Wall> walls;
  std::vector<Type> types;
public:
  ///How many turns it has been since the beginning of the game
  int turnNumber();
  ///Player Number; either 0 or 1
  int playerID();
  ///Maximum valid position in the X (right) direction.  (0,0) is top left
  int boardX();
  ///Maximum valid position in the Y (down) direction.  (0,0) is top left
  int boardY();
  ///What number game this is for the server
  int gameNumber();
  ///Player 0's time remaining
  int player0Time();
  ///Player 1's time remaining
  int player1Time();
  ///Player 0's name
  char* player0Name();
  ///Player 1's name
  char* player1Name();
  
  BaseAI(Connection* c);
  virtual ~BaseAI();
  ///
  ///Make this your username, which should be provided.
  virtual const char* username() = 0;
  ///
  ///Make this your password, which should be provided.
  virtual const char* password() = 0;
  ///
  ///This function is run once, before your first turn.
  virtual void init() = 0;
  ///
  ///This function is called each time it is your turn
  ///Return true to end your turn, return false to ask the server for updated information
  virtual bool run() = 0;
  ///
  ///This function is called after the last turn.
  virtual void end() = 0;


  bool startTurn();
};

#endif
