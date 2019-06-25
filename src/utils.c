//
// Created by Luca Cappelletti on 2019-06-25.
//

#include "utils.h"

void swap(int *xp, int *yp)
{
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}