# -*- coding: iso-8859-1 -*-
class Mappable:
  def __init__(self, game, id, x, y):
    self.game = game
    self.id = id
    self.x = x
    self.y = y

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      ]
    return value

  def nextTurn(self):
    pass



class Unit(Mappable):
  def __init__(self, game, id, x, y, owner, health, maxHealth, size):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.health = health
    self.maxHealth = maxHealth
    self.size = size

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      self.health,
      self.maxHealth,
      self.size,
      ]
    return value

  def nextTurn(self):
    pass

  def talk(self, message):
    self.game.animations.append(['talk', self.id, message])
    return True

  def _distance(self, target):
    x = 0
    y = 0
    if self.x > target.x + target.size-1:
      x = self.x - (target.x + target.size-1)
    elif target.x > self.x + self.size-1:
      x = target.x - (self.x + self.size-1)
    if self.y > target.y + target.size-1:
      y = self.y - (target.y + target.size-1)
    elif target.y > self.y + self.size-1:
      y = target.y - (self.y + self.size-1)
    return x + y

  def _takeDamage(self, damage):
    self.health -= damage
    if self.health < 1 and self.id in self.game.objects:
      self.game.removeObject(self)



class Bot(Unit):
  def __init__(self, game, id, x, y, owner, health, maxHealth, size, actions, steps, damage, range, movitude, actitude, buildRate, partOf, building, type):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.health = health
    self.maxHealth = maxHealth
    self.size = size
    self.actions = actions
    self.steps = steps
    self.damage = damage
    self.range = range
    self.movitude = movitude
    self.actitude = actitude
    self.buildRate = buildRate
    self.partOf = partOf
    self.building = building
    self.type = type

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      self.health,
      self.maxHealth,
      self.size,
      self.actions,
      self.steps,
      self.damage,
      self.range,
      self.movitude,
      self.actitude,
      self.buildRate,
      self.partOf,
      self.building,
      self.type,
      ]
    return value

  @staticmethod
  def fromType(game, x, y, owner, type):
    id = game.nextid
    game.nextid += 1
    return Bot(game, id, x, y, owner, type.maxHealth,  type.maxHealth, 1, 0, 0, type.damage, type.range, type.movitude, type.actitude,
      type.buildRate, 0, 0, type.id)

  def _takeDamage(self, damage):
    if self.building and self.building in self.game.objects and self.health <= damage:
      self.game.removeObject(self.game.objects[self.building])
    Unit._takeDamage(self, damage)
    if self.health <= 0:
      if self.size > 1:
        for i in self.game.objects.values():
          if isinstance(i, Bot) and i.partOf == self.id:
            i._takeDamage(i.health)
        
    if self.health > self.maxHealth:
      self.health = self.maxHealth

  def _combine(self, bot2, bot3, bot4):
    bots = [self, bot2, bot3, bot4]
    id = self.game.nextid
    self.game.nextid += 1

    type = 0
    if self.type == bot2.type == bot3.type == bot4.type:
      type = self.type
    #I am so sorry.
    #This calls the Bot constructor, taking the min or sum of the mini bot values as appropriate
    newBot = Bot(self.game, id, min([i.x for i in bots]), min([i.y for i in bots]), self.owner, sum([i.health for i in bots]),
      sum([i.maxHealth for i in bots]), self.size * 2, 0, 0, sum([i.damage for i in bots]), sum([i.range for i in bots]),
      sum([i.movitude for i in bots]), sum([i.actitude for i in bots]), sum([i.buildRate for i in bots]), 0, 0, type)
    self.game.addObject(newBot)
    for i in bots:
      i.partOf = id
      i.actions = 0
      i.steps = 0
    return newBot

  def _move(self, x, y):
    self.x += x
    self.y += y
    if self.size > 1:
      for i in self.game.objects.values():
        if isinstance(i, Bot):
          if i.partOf == self.id:
            i._move(x, y)

  @staticmethod
  def makeBot(game, x, y, owner, type, size):
    if size == 1:
      bot = Bot.fromType(game, x, y, owner, type)
      game.addObject(bot)
      return bot
    bot1 = Bot.makeBot(game, x, y, owner, type, size/2)
    bot2 = Bot.makeBot(game, x+size/2, y, owner, type, size/2)
    bot3 = Bot.makeBot(game, x, y+size/2, owner, type, size/2)
    bot4 = Bot.makeBot(game, x+size/2, y+size/2, owner, type, size/2)
    return bot1._combine(bot2, bot3, bot4)

  def nextTurn(self):
    self.actions = 0
    self.steps = 0
    if self.game.playerID != self.owner:
      return True
    if self.partOf != 0:
      return True
    if self.building and self.building not in self.game.objects:
      self.building = 0
    if self.building == 0:
      self.actions = self.actitude / self.size**2
      self.steps = self.movitude / self.size**2
      return True
    else:
      baby =  self.game.objects[self.building]
      baby.completionTime -= 1
      if baby.completionTime < 1:
        type = self.game.objects[baby.type]
        newBot = Bot.makeBot(self.game, baby.x, baby.y, self.owner, type, baby.size)
        self.game.removeObject(baby)
        self.building = 0
        self.nextTurn()
        newBot.nextTurn()
        return True
      else:
        return True


  def move(self, direction):
    d = direction[0].lower()
    if d not in 'udlr':
      return "%s is not a direction." % d
    if self.steps < 1:
      return "Out of steps."
    x = y = 0
    if d == 'u':
      y = -1
      if self.y <= 0:
        return "Stepping off the world"
    elif d == 'd':
      y = 1
      if self.y+self.size-1 >= self.game.boardY-1:
        return "Stepping off the world"
    elif d == 'l':
      x = -1
      if self.x <= 0:
        return "Stepping off the world"
    elif d == 'r':
      x = 1
      if self.x+self.size-1 >= self.game.boardX-1:
        return "Stepping off the world"

    victims = []
    for i in self.game.objects.values():
      if isinstance(i, Unit):
        if self._distance(i) == 1:
          if not isinstance(i, Bot) or i.partOf == 0:
            victims.append(i)
    
    if x == -1:
      victims = [i for i in victims if i.x + i.size == self.x]
    elif y == -1:
      victims = [i for i in victims if i.y + i.size == self.y]
    elif x == 1:
      victims = [i for i in victims if i.x == self.x + self.size]
    elif y == 1:
      victims = [i for i in victims if i.y == self.y + self.size]

    if victims:
      victimHealth = sum([i.health for i in victims])
      
      damage = min(victimHealth, self.size**2) * self.game.shattertude
      self._takeDamage(damage)
      
      for i in victims:
        damage = (i.health * self.size**2 + victimHealth - 1) / victimHealth * self.game.shattertude
        self.game.animations.append(['collide', self.id, i.id, d])
        i._takeDamage(damage)
      victims = [i for i in victims if i.health > 0]
    
    if not victims:
      self.game.animations.append(['move', self.id, d])
      self._move(x, y)
    
    self.steps -= 1
    
    return True

  def attack(self, target):
    if self.damage == 0:
      return "Bot unable to attack, damage score = 0"
    if self._distance(target) > (self.range + 1):
      return "Target out of range. self id: %d target id: %d" % (self.id, target.id)
    if isinstance(target, Bot) and target.partOf:
      return "Cannot attack a subbot. self id: %d target id: %d" % (self.id, target.id)

    if self.actions < 1:
      return "Out of actions."
    self.actions -= 1

    self.game.animations.append(['attack', self.id, target.id])
    target._takeDamage(self.damage)

    return True

  def heal(self, target):
    if self.buildRate == 0:
      return "Bot unable to heal, build score = 0"
    if self._distance(target) > (self.range + 1):
      return "Target out of range. self id: %d target id: %d" % (self.id, target.id)
    if target.owner != self.owner:
      return "Cannot heal enemies. self id: %d target id: %d" % (self.id, target.id)
    if target.health == target.maxHealth:
      return "Target fully healed. self id: %d target id: %d" % (self.id, target.id)

    if self.actions < 1:
      return "Out of actions."
    self.actions -= 1

    self.game.animations.append(['heal', self.id, target.id])
    target._takeDamage(-target.maxHealth * self.buildRate / (4 * target.size**2))
    
    self.game.animations.append(['heal', self.id, target.id])

    return True

  def build(self, type, x, y, size):
    if self.buildRate == 0:
      return "Bot unable to build, build score = 0"
    if self.actions < 1:
      return "Out of actions"
    if x < 0 or y < 0 or x+size > self.game.boardX or y+size > self.game.boardY:
      return "Building off the world"
    if size > self.size:
      return "Building a robot larger than itself."
    if size not in [1, 2 ,4, 8, 16, 32]:
      return "Building a robot not a size that is a power of 2"
      

    completionTime = max(8 * size**2 / self.buildRate, 1)
    health = min(type.maxHealth * self.buildRate / 8, type.maxHealth * size**2)
    f = Frame(self.game, 0, x, y, self.owner, health, type.maxHealth * size**2, size, type.id, completionTime)
    if f._distance(self) != 1:
      return "Target is non-adjacent."
    for i in self.game.objects.values():
      if isinstance(i, Unit):
        if f._distance(i) == 0:
          return "Overlap."
    f.id = self.game.nextid
    self.game.nextid += 1
    self.game.addObject(f)
    self.actions = 0
    self.steps = 0
    self.building = f.id
    
    self.game.animations.append(['build', self.id, f.id])

    return True

  def combine(self, bot2, bot3, bot4):
    bots = [self, bot2, bot3, bot4]
    if min([i.actions for i in bots]) < 1:
      return "Not every bot has actions."
    if not self.size == bot2.size == bot3.size == bot4.size:
      return "Not every bot is the same size."
    x = min([i.x for i in bots])
    y = min([i.y for i in bots])
    s = self.size
    pos = [(i.x, i.y) for i in bots]
    if (not (x, y) in pos) or (not (x+s, y) in pos) or (not (x, y+s) in pos) or (not (x+s, y+s) in pos):
      return "Bots not in a square."
    self._combine(bot2, bot3, bot4)

    return True

  def split(self):
    if self.actions < 1:
      return "No actions left."
    if self.size < 2:
      return "Not compound."
    percentHealth = float(self.health) / self.maxHealth
    for i in self.game.objects.values():
      if isinstance(i, Bot):
        if i.partOf == self.id:
          i.partOf = 0
          i.health = int(i.maxHealth * percentHealth)
          if i.health <= 0:
            i.health = 1
    self.game.animations.append(['split', self.id])
    self.game.removeObject(self)

    return True


  def maxActions(self):
    pass

  def moveRate(self):
    for i in self.game.objects.values():
      if isinstance(i, Bot):
        if i.partOf == self.id:
          pass


class Frame(Unit):
  def __init__(self, game, id, x, y, owner, health, maxHealth, size, type, completionTime):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.health = health
    self.maxHealth = maxHealth
    self.size = size
    self.type = type
    self.completionTime = completionTime
    self.totalTime = completionTime

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      self.health,
      self.maxHealth,
      self.size,
      self.type,
      self.completionTime,
      ]
    return value

  def nextTurn(self):
    if self.game.playerID == self.owner:
      self.health += self.maxHealth/self.totalTime



class Type:
  def __init__(self, game, id, name, maxHealth, damage, range, movitude, actitude, buildRate):
    self.game = game
    self.id = id
    self.name = name
    self.maxHealth = maxHealth
    self.damage = damage
    self.range = range
    self.movitude = movitude
    self.actitude = actitude
    self.buildRate = buildRate

  def toList(self):
    value = [
      self.id,
      self.name,
      self.maxHealth,
      self.damage,
      self.range,
      self.movitude,
      self.actitude,
      self.buildRate,
      ]
    return value

  def nextTurn(self):
    pass

class Wall(Unit):
  def __init__(self, game, id, x, y, owner, health, maxHealth, size):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.health = health
    self.maxHealth = maxHealth
    self.size = size

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      self.health,
      self.maxHealth,
      self.size,
      ]
    return value

  @staticmethod
  def make(game, x, y, health):
    id = game.nextid
    game.nextid += 1
    return Wall(game, id, x, y, -1, health,  health, 1)

  def nextTurn(self):
    pass

  def talk(self, message):
    pass
