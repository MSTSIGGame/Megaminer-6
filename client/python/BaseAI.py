# -*- python -*-

from library import library

class BaseAI:
  """@brief A basic AI interface.

  This class implements most the code an AI would need to interface with the lower-level game code.
  AIs should extend this class to get a lot of builer-plate code out of the way
  The provided AI class does just that.
  """
  initialized = False
  iteration = 0
  runGenerator = None
  connection = None
  bots = []
  frames = []
  walls = []
  types = []

  def startTurn(self):
    from GameObject import Bot
    from GameObject import Frame
    from GameObject import Wall
    from GameObject import Type

    BaseAI.bots = [Bot(library.getBot(self.connection, i)) for i in xrange(library.getBotCount(self.connection))]
    BaseAI.frames = [Frame(library.getFrame(self.connection, i)) for i in xrange(library.getFrameCount(self.connection))]
    BaseAI.walls = [Wall(library.getWall(self.connection, i)) for i in xrange(library.getWallCount(self.connection))]
    BaseAI.types = [Type(library.getType(self.connection, i)) for i in xrange(library.getTypeCount(self.connection))]

    if not self.initialized:
      self.initialized = True
      self.init()
    BaseAI.iteration += 1;
    if self.runGenerator:
      try:
        return self.runGenerator.next()
      except StopIteration:
        self.runGenerator = None
    r = self.run()
    if hasattr(r, '__iter__'):
      self.runGenerator = r
      return r.next()
    return r
  
  def turnNumber(self):
    return library.getTurnNumber(self.connection)

  def playerID(self):
    return library.getPlayerID(self.connection)

  def boardX(self):
    return library.getBoardX(self.connection)

  def boardY(self):
    return library.getBoardY(self.connection)

  def gameNumber(self):
    return library.getGameNumber(self.connection)

  def player0Time(self):
    return library.getPlayer0Time(self.connection)

  def player1Time(self):
    return library.getPlayer1Time(self.connection)

  def __init__(self, connection):
    self.connection = connection
