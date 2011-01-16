# -*- python -*-

from library import library

from ExistentialError import ExistentialError

class GameObject(object):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration


##An object that exists on the grid
class Mappable(GameObject):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.mappableGetId(ptr)

  ##Unique Identifier
  def getId(self):
    self.validify()
    return library.mappableGetId(self.ptr)

  ##The X position of the top left corner of this object.  X is horizontal
  def getX(self):
    self.validify()
    return library.mappableGetX(self.ptr)

  ##The Y position of the top left corner of this object.  Y is vertical
  def getY(self):
    self.validify()
    return library.mappableGetY(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    return ret

##An object that exists on the grid
class Unit(Mappable):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.unitGetId(ptr)

  ##Sends a message to be visualized when this unit is selected
  def talk(self, message):
    self.validify()
    return library.unitTalk(self.ptr, message)

  ##Unique Identifier
  def getId(self):
    self.validify()
    return library.unitGetId(self.ptr)

  ##The X position of the top left corner of this object.  X is horizontal
  def getX(self):
    self.validify()
    return library.unitGetX(self.ptr)

  ##The Y position of the top left corner of this object.  Y is vertical
  def getY(self):
    self.validify()
    return library.unitGetY(self.ptr)

  ##The owning player
  def getOwner(self):
    self.validify()
    return library.unitGetOwner(self.ptr)

  ##How much health this unit currently has
  def getHealth(self):
    self.validify()
    return library.unitGetHealth(self.ptr)

  ##The maximum amount of health this unit can ever have
  def getMaxHealth(self):
    self.validify()
    return library.unitGetMaxHealth(self.ptr)

  ##The length of one side of this Unit
  def getSize(self):
    self.validify()
    return library.unitGetSize(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    ret += "owner: %s\n" % self.getOwner()
    ret += "health: %s\n" % self.getHealth()
    ret += "maxHealth: %s\n" % self.getMaxHealth()
    ret += "size: %s\n" % self.getSize()
    return ret

##The bot class.
class Bot(Unit):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.botGetId(ptr)

  def validify(self):
    from BaseAI import BaseAI
    #if this class is pointing to an object from before the current turn it's probably
    #somewhere else in memory now
    if self.iteration == BaseAI.iteration:
      return True
    for i in BaseAI.bots:
      if i.id == self.id:
        self.ptr = i.ptr
        self.iteration = BaseAI.iteration
        return True
    raise ExistentialError()
  ##Sends a message to be visualized when this unit is selected
  def talk(self, message):
    self.validify()
    return library.botTalk(self.ptr, message)

  ##Move in the indicated direction (U, D, L, or R).  U is y=y-1, L=x=x-1, such that the top left corner is (0,0). Requires the calling robot to have a step.
  def move(self, direction):
    self.validify()
    return library.botMove(self.ptr, direction)

  ##Attack the specified unit.  Requires the calling robot to have an action and for the target to be in range
  def attack(self, target):
    self.validify()
    if not isinstance(target, Unit):
      raise TypeError('target should be of [Unit]')
    target.validify()
    return library.botAttack(self.ptr, target.ptr)

  ##Heals the indicated bot.  Requires the calling robot to have an action and for the target to be in range.  Heals for target.maxHealth * self.buildRate / (4 * target.size^2)
  def heal(self, target):
    self.validify()
    if not isinstance(target, Bot):
      raise TypeError('target should be of [Bot]')
    target.validify()
    return library.botHeal(self.ptr, target.ptr)

  ##Begins building a new robot.  While building, the new robot will be a frame.  Requires the calling robot to have an action. X and Y must cause the new robot to be adjacent.  Size must be less than or equal to the calling robots size.  Completes in 8 * size^2 / self.buildRate turns
  def build(self, type, x, y, size):
    self.validify()
    if not isinstance(type, Type):
      raise TypeError('type should be of [Type]')
    type.validify()
    return library.botBuild(self.ptr, type.ptr, x, y, size)

  ##Combines four robots into one.  Requires all robots to have an action, be of the same size, and be arranged in a square
  def combine(self, bot2, bot3, bot4):
    self.validify()
    if not isinstance(bot2, Bot):
      raise TypeError('bot2 should be of [Bot]')
    bot2.validify()
    if not isinstance(bot3, Bot):
      raise TypeError('bot3 should be of [Bot]')
    bot3.validify()
    if not isinstance(bot4, Bot):
      raise TypeError('bot4 should be of [Bot]')
    bot4.validify()
    return library.botCombine(self.ptr, bot2.ptr, bot3.ptr, bot4.ptr)

  ##Splits a compound bot into the 4 robots that combined to make it.  Requires the calling robot to have an action.
  def split(self):
    self.validify()
    return library.botSplit(self.ptr)

  ##Returns the maximum number of actions this robot can take per turn.
  def maxActions(self):
    self.validify()
    return library.botMaxActions(self.ptr)

  ##Returns the maximum number of steps this robot can take per turn.
  def maxSteps(self):
    self.validify()
    return library.botMaxSteps(self.ptr)

  ##Unique Identifier
  def getId(self):
    self.validify()
    return library.botGetId(self.ptr)

  ##The X position of the top left corner of this object.  X is horizontal
  def getX(self):
    self.validify()
    return library.botGetX(self.ptr)

  ##The Y position of the top left corner of this object.  Y is vertical
  def getY(self):
    self.validify()
    return library.botGetY(self.ptr)

  ##The owning player
  def getOwner(self):
    self.validify()
    return library.botGetOwner(self.ptr)

  ##How much health this unit currently has
  def getHealth(self):
    self.validify()
    return library.botGetHealth(self.ptr)

  ##The maximum amount of health this unit can ever have
  def getMaxHealth(self):
    self.validify()
    return library.botGetMaxHealth(self.ptr)

  ##The length of one side of this Unit
  def getSize(self):
    self.validify()
    return library.botGetSize(self.ptr)

  ##How many actions this bot can still perform
  def getActions(self):
    self.validify()
    return library.botGetActions(self.ptr)

  ##How many steps this bot can still take
  def getSteps(self):
    self.validify()
    return library.botGetSteps(self.ptr)

  ##The amount of damage this robot does when attacking
  def getDamage(self):
    self.validify()
    return library.botGetDamage(self.ptr)

  ##How far this robot can attack or heal from its edge
  def getRange(self):
    self.validify()
    return library.botGetRange(self.ptr)

  ##This value divided by the number of bots = maxSteps for this robot
  def getMovitude(self):
    self.validify()
    return library.botGetMovitude(self.ptr)

  ##This value divided by the number of bots = maxActions for this robot
  def getActitude(self):
    self.validify()
    return library.botGetActitude(self.ptr)

  ##This value is used to determine how many turns it takes to build a robot and how much this robot heals for
  def getBuildRate(self):
    self.validify()
    return library.botGetBuildRate(self.ptr)

  ##ID of the robot this robot is apart of, 0 if not in a robot
  def getPartOf(self):
    self.validify()
    return library.botGetPartOf(self.ptr)

  ##ID of the robot this robot is building, 0 if not building
  def getBuilding(self):
    self.validify()
    return library.botGetBuilding(self.ptr)

  ##ID of the type this robot is, 0 if a combination
  def getType(self):
    self.validify()
    return library.botGetType(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    ret += "owner: %s\n" % self.getOwner()
    ret += "health: %s\n" % self.getHealth()
    ret += "maxHealth: %s\n" % self.getMaxHealth()
    ret += "size: %s\n" % self.getSize()
    ret += "actions: %s\n" % self.getActions()
    ret += "steps: %s\n" % self.getSteps()
    ret += "damage: %s\n" % self.getDamage()
    ret += "range: %s\n" % self.getRange()
    ret += "movitude: %s\n" % self.getMovitude()
    ret += "actitude: %s\n" % self.getActitude()
    ret += "buildRate: %s\n" % self.getBuildRate()
    ret += "partOf: %s\n" % self.getPartOf()
    ret += "building: %s\n" % self.getBuilding()
    ret += "type: %s\n" % self.getType()
    return ret

##A baby robot.
class Frame(Unit):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.frameGetId(ptr)

  def validify(self):
    from BaseAI import BaseAI
    #if this class is pointing to an object from before the current turn it's probably
    #somewhere else in memory now
    if self.iteration == BaseAI.iteration:
      return True
    for i in BaseAI.frames:
      if i.id == self.id:
        self.ptr = i.ptr
        self.iteration = BaseAI.iteration
        return True
    raise ExistentialError()
  ##Sends a message to be visualized when this unit is selected
  def talk(self, message):
    self.validify()
    return library.frameTalk(self.ptr, message)

  ##Unique Identifier
  def getId(self):
    self.validify()
    return library.frameGetId(self.ptr)

  ##The X position of the top left corner of this object.  X is horizontal
  def getX(self):
    self.validify()
    return library.frameGetX(self.ptr)

  ##The Y position of the top left corner of this object.  Y is vertical
  def getY(self):
    self.validify()
    return library.frameGetY(self.ptr)

  ##The owning player
  def getOwner(self):
    self.validify()
    return library.frameGetOwner(self.ptr)

  ##How much health this unit currently has
  def getHealth(self):
    self.validify()
    return library.frameGetHealth(self.ptr)

  ##The maximum amount of health this unit can ever have
  def getMaxHealth(self):
    self.validify()
    return library.frameGetMaxHealth(self.ptr)

  ##The length of one side of this Unit
  def getSize(self):
    self.validify()
    return library.frameGetSize(self.ptr)

  ##What type this robot will be
  def getType(self):
    self.validify()
    return library.frameGetType(self.ptr)

  ##How many of your turns until this frame becomes a robot
  def getCompletionTime(self):
    self.validify()
    return library.frameGetCompletionTime(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    ret += "owner: %s\n" % self.getOwner()
    ret += "health: %s\n" % self.getHealth()
    ret += "maxHealth: %s\n" % self.getMaxHealth()
    ret += "size: %s\n" % self.getSize()
    ret += "type: %s\n" % self.getType()
    ret += "completionTime: %s\n" % self.getCompletionTime()
    return ret

##A pile of hard stuff that is in the way.
class Wall(Unit):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.wallGetId(ptr)

  def validify(self):
    from BaseAI import BaseAI
    #if this class is pointing to an object from before the current turn it's probably
    #somewhere else in memory now
    if self.iteration == BaseAI.iteration:
      return True
    for i in BaseAI.walls:
      if i.id == self.id:
        self.ptr = i.ptr
        self.iteration = BaseAI.iteration
        return True
    raise ExistentialError()
  ##Sends a message to be visualized when this unit is selected
  def talk(self, message):
    self.validify()
    return library.wallTalk(self.ptr, message)

  ##Unique Identifier
  def getId(self):
    self.validify()
    return library.wallGetId(self.ptr)

  ##The X position of the top left corner of this object.  X is horizontal
  def getX(self):
    self.validify()
    return library.wallGetX(self.ptr)

  ##The Y position of the top left corner of this object.  Y is vertical
  def getY(self):
    self.validify()
    return library.wallGetY(self.ptr)

  ##The owning player
  def getOwner(self):
    self.validify()
    return library.wallGetOwner(self.ptr)

  ##How much health this unit currently has
  def getHealth(self):
    self.validify()
    return library.wallGetHealth(self.ptr)

  ##The maximum amount of health this unit can ever have
  def getMaxHealth(self):
    self.validify()
    return library.wallGetMaxHealth(self.ptr)

  ##The length of one side of this Unit
  def getSize(self):
    self.validify()
    return library.wallGetSize(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    ret += "owner: %s\n" % self.getOwner()
    ret += "health: %s\n" % self.getHealth()
    ret += "maxHealth: %s\n" % self.getMaxHealth()
    ret += "size: %s\n" % self.getSize()
    return ret

##A kind of robot.
class Type(GameObject):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.typeGetId(ptr)

  def validify(self):
    from BaseAI import BaseAI
    #if this class is pointing to an object from before the current turn it's probably
    #somewhere else in memory now
    if self.iteration == BaseAI.iteration:
      return True
    for i in BaseAI.types:
      if i.id == self.id:
        self.ptr = i.ptr
        self.iteration = BaseAI.iteration
        return True
    raise ExistentialError()
  ##Unique Identifier
  def getId(self):
    self.validify()
    return library.typeGetId(self.ptr)

  ##The name of this type of robot
  def getName(self):
    self.validify()
    return library.typeGetName(self.ptr)

  ##The maximum amount of health for this type of robot
  def getMaxHealth(self):
    self.validify()
    return library.typeGetMaxHealth(self.ptr)

  ##The amount of damage this type of robot does when attacking
  def getDamage(self):
    self.validify()
    return library.typeGetDamage(self.ptr)

  ##How far this type of robot can attack or heal from its edge
  def getRange(self):
    self.validify()
    return library.typeGetRange(self.ptr)

  ##This value divided by the number of bots = maxSteps for this type of robot
  def getMovitude(self):
    self.validify()
    return library.typeGetMovitude(self.ptr)

  ##This value divided by the number of bots = maxActions for this type of robot
  def getActitude(self):
    self.validify()
    return library.typeGetActitude(self.ptr)

  ##This value is used to determine how many turns it takes to build a robot and how much this type of robot heals for
  def getBuildRate(self):
    self.validify()
    return library.typeGetBuildRate(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "name: %s\n" % self.getName()
    ret += "maxHealth: %s\n" % self.getMaxHealth()
    ret += "damage: %s\n" % self.getDamage()
    ret += "range: %s\n" % self.getRange()
    ret += "movitude: %s\n" % self.getMovitude()
    ret += "actitude: %s\n" % self.getActitude()
    ret += "buildRate: %s\n" % self.getBuildRate()
    return ret
