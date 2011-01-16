# -*- coding: iso-8859-1 -*-
from functools import wraps

def verifyReferences(self, expression, references):
  for i in range(0, len(references)):
    if references[i] is not None:
      if expression[i] not in self.objects:
        return str(expression[i]) + " does not exist"
      if not isinstance(self.objects[expression[i]], references[i]):
        return str(expression[i]) + " does not reference a " + references[i].__name__
  return True


def requireReferences(*n):
  def dec(f):
    @wraps(f)
    def wrapper(self, *expression):
      errMsg = verifyReferences(self, expression, n)
      if not (errMsg == True):
        return errMsg
      return f(self, *expression)
    return wrapper
  return dec

def deref(self, type, id):
  if type is None:
    return id
  if id not in self.objects:
    raise LookupError(str(id) + " does not exist")
  if not isinstance(self.objects[id], type):
    raise LookupError(str(id) + " does not reference a " + type.__name__)
  return self.objects[id]

def derefArgs(*types):
  def dec(f):
    @wraps(f)
    def wrapper(self, *values):
      try:
        args = [deref(self, i, j) for i, j in zip(types, values)]
      except LookupError as e:
        return e.args[0]
      else:
        return f(self, *args)
    return wrapper
  return dec

def requireOwn(func):
  """
  A decorator.
  Prevents this method from running successfully unless the connection
  is logged in, associated with a game, and is the current player
  """
  def wrappedFunc(self, unit,*args):
    if unit.owner != self.playerID is not self:
      return "You do not own %s" % unit.id
    else:
      return func(self, unit, *args)
  return wrappedFunc
