class Util
{
  ///Given the x,y and size of two bots, returns the Manhattan distance
  static int distance(int fromX, int fromY, int fromSize, int toX, int toY, int toSize)
  {
    return Client.INSTANCE.distance(fromX, fromY, fromSize, toX, toY, toSize); 
  }

}


