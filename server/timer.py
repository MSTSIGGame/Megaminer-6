import aspects

from game_app.match import Match

from twisted.internet import reactor

games = []

def install():
  def wrapNextTurn(self):
    if self not in games:
      games.append(self)
    if self.turn == self.players[0]:
      self.player1Time += self.timeInc
    elif self.turn == self.players[1]:
      self.player0Time += self.timeInc
    retval = yield aspects.proceed

  aspects.with_wrap(wrapNextTurn, Match.nextTurn)

  def tick():
    import main
    for i in games:
      if i.turn == i.players[0]:
        i.player0Time -= 1
        if i.player0Time < 0:
          i.declareWinner(i.players[1], 'Laaaaaag')
      elif i.turn == i.players[1]:
        i.player1Time -= 1
        if i.player1Time < 0:
          i.declareWinner(i.players[0], 'Laaaaaag')
      else:
        games.remove(i)

    reactor.callLater(1, tick)

  reactor.callWhenRunning(reactor.callLater, 1, tick)
        
