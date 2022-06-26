#include "lal.h"
#include <iostream>
#include <vector>
int y = 10,x=10;
std::vector<std::vector<int>> mainfield(y, std::vector<int>(x));
bool zero_vector() {
   int t = 0;
   for (int i = 0; i < y; i++)
      for (int j = 0; j < x; j++)
      {
         mainfield[i][j] = 0;
         t++;
      }
   if (t==x*y)
      return true;
   else
      return false;
}
