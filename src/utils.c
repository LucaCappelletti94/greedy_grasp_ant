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

int int_min(const int* values, int n)
{
  int min=INT_MAX;
  for(int i=0; i<n; i++)
    if(min>values[i])
      min = values[i];
  return min;
}

int int_max(const int* values, int n)
{
  int max=0;
  for(int i=0; i<n; i++)
    if(max<values[i])
      max = values[i];
  return max;
}

int int_mean(const int* values, int n)
{
  int sum, i;
  for(i=sum=0; i<n; sum+=values[i], i++);
  return sum/n;
}

int int_var(const int* values, int n)
{
  int sum, i;
  int mean = int_mean(values, n);
  for(i=sum=0; i<n; i++)
  {
    sum += (int)pow(mean - values[i], 2);
  }
  return sum/n;
}

int int_std(const int* values, int n)
{
  return (int)sqrt(int_var(values, n));
}