#ifndef UTIL_H
#define UTIL_H

#ifdef __cplusplus
extern "C"
{
#endif

///Given the x,y and size of two bots, returns the Manhattan distance
int distance(int fromX, int fromY, int fromSize, int toX, int toY, int toSize);
  
#ifdef __cplusplus
}
#endif

#endif


