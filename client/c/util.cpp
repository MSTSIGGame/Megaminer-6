//This file is for any functions you want to write that aren't directly part of your AI
//This file is shared, meaning the Java and Python clients can access it too if you want C++ code for whatever reason
#include "util.h"

int distance(int fromX, int fromY, int fromSize, int toX, int toY, int toSize)
{
  int x = 0, y = 0;
  if(fromX > toX + toSize-1)
    x = fromX - (toX + toSize-1);
  else if(toX > fromX + fromSize-1)
    x = toX - (fromX + fromSize-1);
  if(fromY > toY + toSize-1)
    y = fromY - (toY + toSize-1);
  else if(toY > fromY + fromSize-1)
    y = toY - (fromY + fromSize-1);
  return x + y;
}