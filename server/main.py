#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
from networking.sexpr.sexpr import sexpr2str
from networking.dispatch import SexpProtocol
from networking.apps import BaseApp, protocolmethod, namedmethod, AccountsAppMixin
from itertools import repeat
import functools
import game_app.match
Match = game_app.match.Match
from game_app.game_app_utils import errorBuffer, requireLogin, requireGame,                   requireTurn, requireTypes
import time
import struct
import bz2
import sys


class GameApp(AccountsAppMixin, BaseApp):
  games = {}
  nextid = 1

  def __init__(self, protocol):
    BaseApp.__init__(self, protocol)
    AccountsAppMixin.__init__(self)
    self.game = None
    self.user = self.name
    self.screenName = self.name

  @protocolmethod
  @requireLogin
  def createGame(self):
    """ Creates a game """
    if self.game is not None:
      return ("create-game-denied", "You are already in a game.")
    else:
      self.user = self.name
      self.game = Match(GameApp.nextid, self)
      self.game.addPlayer(self)
      GameApp.games[GameApp.nextid] = self.game
      GameApp.nextid += 1
      return ("create-game", self.game.id)

  @protocolmethod
  @requireLogin
  @requireTypes(None, int)
  def joinGame(self, gameNumber):
    """ Joins the specified game"""    
    if self.game is not None:
      return ["join-game-denied", "You are already in a game"]
    try:
      self.user = self.name
      if gameNumber == 0: #join any option, joins available game with lowest number
        for game in GameApp.games:
          self.game = GameApp.games[game]
          temp = self.game.addPlayer(self)
          if temp and type(temp) == type(bool()):
            gameNumber = game
            break
          else:
            self.game = None
        if self.game is None:
          return ["join-game-denied", "No games available"]
      else: #join a specific game, gameNumber >= 1
        self.game = GameApp.games[gameNumber]
        temp = self.game.addPlayer(self)
        if type(temp) != type(bool()) or not temp:
          self.game = None
          return ["join-game-denied", "Game is full"]
      return ["join-accepted", gameNumber]
    except KeyError:
      return ["join-game-denied", "No such game"]

  @protocolmethod
  @errorBuffer
  @requireGame
  def leaveGame(self):
    """ Leaves the current game """
    if self.game is None:
      return "Not in a game"
    reply = self.game.removePlayer(self)
    if ((len(self.game.players) == 0)):
      del GameApp.games[self.game.id]
    self.game = None
    return reply

  @protocolmethod
  @errorBuffer
  @requireGame
  def gameStart(self):
    """Starts game associated with this connections """
    return self.game.start()

  @protocolmethod
  @errorBuffer
  @requireGame
  def gameStatus(self):
    """ Requests the status of your game """
    return self.game.sendStatus([self])

  @protocolmethod
  @errorBuffer
  @requireTurn
  def endTurn(self):
    """ Attempts to end your turn """
    return self.game.nextTurn()

  @protocolmethod
  @errorBuffer
  @requireTurn
  @requireTypes(None, int, str)
  def gameTalk(self, unit, talk_string):
    """"""
    if self.game.turn is not self:
      return "Not your turn."
    return self.game.talk(unit, talk_string)

  @protocolmethod
  @errorBuffer
  @requireTurn
  @requireTypes(None, int, str)
  def gameMove(self, bot, direction):
    """"""
    if self.game.turn is not self:
      return "Not your turn."
    return self.game.move(bot, direction)

  @protocolmethod
  @errorBuffer
  @requireTurn
  @requireTypes(None, int, int)
  def gameAttack(self, bot, target):
    """"""
    if self.game.turn is not self:
      return "Not your turn."
    return self.game.attack(bot, target)

  @protocolmethod
  @errorBuffer
  @requireTurn
  @requireTypes(None, int, int)
  def gameHeal(self, bot, target):
    """"""
    if self.game.turn is not self:
      return "Not your turn."
    return self.game.heal(bot, target)

  @protocolmethod
  @errorBuffer
  @requireTurn
  @requireTypes(None, int, int, int, int, int)
  def gameBuild(self, bot, type, x, y, size):
    """"""
    if self.game.turn is not self:
      return "Not your turn."
    return self.game.build(bot, type, x, y, size)

  @protocolmethod
  @errorBuffer
  @requireTurn
  @requireTypes(None, int, int, int, int)
  def gameCombine(self, bot, Bot2, Bot3, Bot4):
    """"""
    if self.game.turn is not self:
      return "Not your turn."
    return self.game.combine(bot, Bot2, Bot3, Bot4)

  @protocolmethod
  @errorBuffer
  @requireTurn
  @requireTypes(None, int)
  def gameSplit(self, bot):
    """"""
    if self.game.turn is not self:
      return "Not your turn."
    return self.game.split(bot)


  @protocolmethod
  def whoami(self):
    """ Returns this connection's session identifiers """
    if self.name:
      return ("num", self.protocol.session_num), ("name", self.name)
    else:
      return ("num", self.protocol.session_num), ("name", "noone")

  @protocolmethod
  @requireLogin
  @requireTypes(None, str)
  def requestLog(self, logID):
    """ Requests a specific gamelog """ 
    infile = bz2.BZ2File("logs/" + logID + ".gamelog.bz2", "r")
    return ['log', logID, infile.read()]

  def writeSExpr(self, message):
    """ Adds backward compatibility with game logic written for the old
    server code
    """
    payload = sexpr2str(message)
    self.protocol.sendString(payload)

class TestGameServer(SexpProtocol):
  app = GameApp

if __name__ == "__main__":
  import timer
  timer.install()
  if '-arena' in sys.argv:
    import arena
    arena.install()
  TestGameServer.main(19000)
