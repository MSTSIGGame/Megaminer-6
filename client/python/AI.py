# -*- coding: iso-8859-1 -*-
#-*-python-*-
from BaseAI import BaseAI
from GameObject import *
import random
import util

class AI(BaseAI):
  """The class implementing gameplay logic."""
  @staticmethod
  def username():
    return "Shell AI"

  @staticmethod
  def password():
    return "password"

  #Jankey Global to keep track of what phase of the grand plan I am in
  stage = 0
  buildCoeff = 8
  #This function is called once, before your first turn
  def init(self):
    pass

  #This function is called each time it is your turn
  #Return true to end your turn, return false to ask the server for updated information
  def run(self):
    print 'I has a Turn!',self.stage
    builders = []
    thorParts = []
    thors = []
    for i in self.bots:
      if i.getOwner() == self.playerID() and i.getPartOf() == 0:
        if i.getType() == 2 and not i.getBuilding():
          builders.append(i)
        elif i.getType() == 0:
          thors.append(i)
        else:
          thorParts.append(i)
    if self.stage == 0:
      for b in builders:
        #builds second set away from enemy
        deltaX = b.getX() - 1 + 2*self.playerID()
        b.build(self.types[1],deltaX,b.getY(),1)
      #waits until builders are almost done, then initiates next stage
      for x in range(self.buildCoeff):
        print 'Waiting for building!'
        yield 1
      print 'Building Complete!'
    if self.stage == 1:
      for b in builders:
        if b.getY() == 9:
          b.talk("I'm movin up!")
          b.move('U')
          b.build(self.types[2],b.getX(),b.getY()+1,1)
        elif b.getY() == 10:
          b.talk("I'm movin Down!")
          b.move('D')
          b.build(self.types[3],b.getX(),b.getY()-1,1)
      self.stage = 2
    if self.stage == 2:
      print "loopey"
      while True:
        builders = []
        thorParts = []
        thors = []
        for i in self.bots:
          if i.getOwner() == self.playerID() and i.getPartOf() == 0:
            if i.getType() == 2 and not i.getBuilding():
              builders.append(i)
            elif i.getType() == 0:
              thors.append(i)
            else:
              thorParts.append(i)
        for b in builders:
          if b.getY() == 8:
            b.build(self.types[2],b.getX(),b.getY()+1,1)
          else:
            b.build(self.types[3],b.getX(),b.getY()-1,1)
        if len(thorParts) == 4:
          thorParts[0].combine(thorParts[1],thorParts[2],thorParts[3])
          thorParts[0].talk("THOR EIZ HERE!")
        for t in thors:
          mTarget = self.findMoveTarget(t)
          self.moveOrKite(t,mTarget)
          aTarget = self.findAttackTarget(t)
          if aTarget:
            t.attack(aTarget)
            t.talk("BOOM!")
          if t.getSteps() > 0:
            mTarget = self.findMoveTarget(t)
            self.moveOrKite(t,mTarget)
        yield 1
    if self.stage == 0:
      self.stage = 1
    print 'I done with turn!'
        
  def findAttackTarget(self,u):
    for e in self.bots:
      if self.playerID() != e.getOwner() and e.getPartOf() == 0:
        if inRange(u,e):
          return e
    for f in self.frames:
      if self.playerID() != f.getOwner(): 
        if inRange(u,f):
          return f
    for w in self.walls:
      if w.getOwner() == -1:
        if inRange(u,w):
          return w
    return False

   
  def findMoveTarget(self, unit):
        enemies = [i for i in self.bots if i.getOwner() == 0 and self.playerID() == 1 and i.getPartOf() == 0 or i.getOwner() == 1 and self.playerID() == 0 and i.getPartOf() == 0]
        targetDist = util.distance(unit.getX(),unit.getY(),unit.getSize(),enemies[0].getX(),enemies[0].getY(),enemies[0].getSize())
        target = enemies[0]
        for e in enemies:
          if util.distance(unit.getX(),unit.getY(),unit.getSize(),e.getX(),e.getY(),e.getSize()) < targetDist:
            target = e
            targetDist = util.distance(unit.getX(),unit.getY(),unit.getSize(),e.getX(),e.getY(),e.getSize())
        return target
        
  def moveOrKite(self, unit, target):
    if util.distance(unit.getX(),unit.getY(),unit.getSize(),target.getX(),target.getY(),target.getSize()) >= unit.getRange():
      if self.playerID() == 0:
        unit.move('R')
      if self.playerID() == 1:
        unit.move('L')
    
  def collisionSafe(self,unit,direction):
    #if I ever care I'll do inteligent collision detection
    return True
  
  def __init__(self, conn):
    BaseAI.__init__(self, conn)
    

def inRange(u, target):
  if u.getRange()+1 >= util.distance(u.getX(),u.getY(),u.getSize(),target.getX(),target.getY(),target.getSize()):
    return True
  else:
    return False
    