# -*- coding: iso-8859-1 -*-
from base import *
from matchUtils import *
from objects import *
import networking.config.config
from collections import defaultdict
from networking.sexpr.sexpr import *
import os
import random
import itertools
import scribe

Scribe = scribe.Scribe

def loadClassDefaults(cfgFile = "config/defaults.cfg"):
  cfg = networking.config.config.readConfig(cfgFile)
  for className in cfg.keys():
    for attr in cfg[className]:
      setattr(eval(className), attr, cfg[className][attr])

class Match(DefaultGameWorld):
  def __init__(self, id, controller):
    self.id = int(id)
    self.controller = controller
    DefaultGameWorld.__init__(self)
    self.scribe = Scribe(self.logPath())
    self.addPlayer(self.scribe, "spectator")

    #TODO: INITIALIZE THESE!
    self.turnNumber = -1
    self.playerID = -1
    self.gameNumber = id
    self.player0Time = self.startTime
    self.player1Time = self.startTime
    
    cfgUnits = networking.config.config.readConfig("config/units.cfg")
    self.initTypes(cfgUnits)
    self.startBots(cfgUnits)
    self.startWalls()

  def initTypes(self, cfg):
    for i in sorted(cfg.keys()):
      if "startbot" not in i.lower():
        self.objects[self.nextid] = Type(self, self.nextid, i, cfg[i]["maxHealth"], cfg[i]["damage"], cfg[i]["range"], cfg[i]["movitude"], cfg[i]["actitude"], cfg[i]["buildRate"])
        self.nextid += 1
    #(self.objects[self.nextid] = Type(self, self.nextid, name, maxHealth, damage, range, movitude, actitude, buildRate)
    #self.nextid += 1
    return cfg

  def startBots(self, cfg):
    for i in cfg.keys():
      if "startbot" in i.lower():
        self.addObject(Bot.fromType(self, cfg[i]["x"], cfg[i]["y"], cfg[i]["owner"], self.objects[cfg[i]["type"]]))

  def startWalls(self):
    walls = 0
    map = [ [' ' for i in xrange(self.boardY)] for j in xrange(self.boardX)]
    x = random.randrange(0, self.boardX)
    y = random.randrange(0, self.boardX)
    while walls < self.maxWalls:
      dx = random.randint(-1, 1)
      dy = random.randint(-1, 1)
      for i in xrange(random.randint(1, self.wallLength)):
        x += dx
        y += dy
        if x < 0 or y < 0 or x >= self.boardX or y >= self.boardY or map[x][y] == '#':
          x = random.randrange(0, self.boardX)
          y = random.randrange(0, self.boardX)
          break
        if random.randint(1, 100) > self.dooritude:
          map[x][y] = '#'
          walls += 1

    for x in xrange(self.boardX):
      for y in xrange(self.boardY):
        if map[x][y] == '#':
           map[self.boardX-x-1][y] = '#'

    for i in self.objects.values():
      if isinstance(i, Bot):
        for x in xrange(i.x-1, i.x+2):
          for y in xrange(i.y-1, i.y+2):
            map[x][y] = ' '

    for i in self.objects.values():
      if isinstance(i, Bot):
        map[i.x][i.y] = chr(ord('a') + i.type - 1)
    
    for x in xrange(self.boardX):
      for y in xrange(self.boardY):
        if map[x][y] == '#':
          self.addObject(Wall.make(self, x, y, self.wallHealth))

  def addPlayer(self, connection, type="player"):
    connection.type = type
    if len(self.players) >= 2 and type == "player":
      return "Game is full"
    if type == "player":
      self.players.append(connection)
    elif type == "spectator":
      self.spectators.append(connection)
      #If the game has already started, send them the ident message
      if (self.turn is not None):
        self.sendIdent([connection])
    return True

  def removePlayer(self, connection):
    if connection in self.players:
      if self.turn is not None:
        winner = self.players[1 - self.getPlayerIndex(connection)]
        self.declareWinner(winner, 'Intimidation')
      self.players.remove(connection)
    else:
      self.spectators.remove(connection)

  def start(self):
    if len(self.players) < 2:
      return "Game is not full"
    if self.winner is not None or self.turn is not None:
      return "Game has already begun"
    
    #TODO: START STUFF

    self.turnNumber = -1
    
    self.sendIdent(self.players + self.spectators)

    self.turn = self.players[1]

    self.nextTurn()
    return True


  def nextTurn(self):
    self.turnNumber += 1
    if self.turn == self.players[0]:
      self.turn = self.players[1]
      self.playerID = 1
    elif self.turn == self.players[1]:
      self.turn = self.players[0]
      self.playerID = 0

    else:
      return "Game is over."

    for obj in self.objects.values():
      obj.nextTurn()

    self.checkWinner()
    if self.winner is None:
      self.sendStatus([self.turn] +  self.spectators)
    else:
      self.sendStatus(self.spectators)
    self.animations = ["animations"]
    return True

  def checkWinner(self):
    if not [i for i in self.objects.values() if isinstance(i, Bot) and i.owner == 0]:
      self.declareWinner(self.players[1], 'Annihilation')
    elif not [i for i in self.objects.values() if isinstance(i, Bot) and i.owner == 1]:
      self.declareWinner(self.players[0], 'Annihilation')
    elif self.turnNumber >= 500:
      numBots = [0 ,0]
      health = [0., 0.]
      maxHealth = [0., 0.]
      for i in self.objects.values():
        if isinstance(i, Bot):
          if i.size == 1:
            numBots[i.owner] += 1
          if i.partOf == 0:
            health[i.owner] += i.health
            maxHealth[i.owner] += i.maxHealth
      percentHealth = [float(health[0]) / maxHealth[0], float(health[1]) / maxHealth[1]]
      if numBots[0] > numBots[1]:
        self.declareWinner(self.players[0], 'Supremacy')
      elif numBots[1] > numBots[0]:
        self.declareWinner(self.players[1], 'Supremacy')
      elif percentHealth[0] > percentHealth[1]:
        self.declareWinner(self.players[0], 'Wellness')
      elif percentHealth[1] > percentHealth[0]:
        self.declareWinner(self.players[1], 'Wellness')
      else:
        self.declareWinner(self.players[1], 'Success')
        

  def declareWinner(self, winner, reason = ''):
    self.winner = winner

    msg = ["game-winner", self.id, self.winner.user, self.getPlayerIndex(self.winner), reason]
    self.scribe.writeSExpr(msg)
    self.scribe.finalize()
    self.removePlayer(self.scribe)

    for p in self.players + self.spectators:
      p.writeSExpr(msg)

    self.sendStatus([self.turn])
    self.playerID ^= 1
    self.sendStatus([self.players[self.playerID]])
    self.playerID ^= 1

    self.turn = None
    
  def logPath(self):
    return "logs/" + str(self.id) + ".gamelog"
  
  @derefArgs(Unit, None)
  @requireOwn
  def talk(self, object, talk_string):
    return object.talk(talk_string, )

  @derefArgs(Bot, None)
  @requireOwn
  def move(self, object, direction):
    return object.move(direction, )

  @derefArgs(Bot,Unit)
  @requireOwn
  def attack(self, object, target):
    return object.attack(target, )

  @derefArgs(Bot,Bot)
  @requireOwn
  def heal(self, object, target):
    return object.heal(target, )


  @derefArgs(Bot, Type, None, None, None)
  @requireOwn
  def build(self, object, type, x, y, size):
    return object.build(type, x, y, size, )

  @derefArgs(Bot, Bot, Bot, Bot)
  @requireOwn
  def combine(self, object, Bot2, Bot3, Bot4):
    return object.combine(Bot2, Bot3, Bot4, )

  @derefArgs(Bot)
  @requireOwn
  def split(self, object):
    return object.split()


  def sendIdent(self, players):
    if len(self.players) < 2:
      return False
    list = []
    for i in itertools.chain(self.players, self.spectators):
      list += [[self.getPlayerIndex(i), i.user, i.screenName, i.type]]
    for i in players:
      i.writeSExpr(['megaminer', 6])
      i.writeSExpr(['ident', list, self.id, self.getPlayerIndex(i)])

  def getPlayerIndex(self, player):
    try:
      playerIndex = self.players.index(player)
    except ValueError:
      playerIndex = -1
    return playerIndex

  def sendStatus(self, players):
    for i in players:
      i.writeSExpr(self.status())
      if i in self.spectators:
        i.writeSExpr(self.animations)
    return True


  def status(self):
    msg = ["status"]

    msg.append(["game", self.turnNumber, self.playerID, self.boardX, self.boardY, self.gameNumber, self.player0Time, self.player1Time])

    typeLists = []
    typeLists.append(["Bot"] + [i.toList() for i in self.objects.values() if i.__class__ is Bot])
    typeLists.append(["Frame"] + [i.toList() for i in self.objects.values() if i.__class__ is Frame])
    typeLists.append(["Wall"] + [i.toList() for i in self.objects.values() if i.__class__ is Wall])
    if self.turnNumber < 2:
      typeLists.append(["Type"] + [i.toList() for i in self.objects.values() if i.__class__ is Type])

    msg.extend(typeLists)

    return msg


loadClassDefaults()

