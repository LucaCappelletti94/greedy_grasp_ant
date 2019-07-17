//
// Created by Luca Cappelletti on 2019-06-25.
//

#ifndef GREEDY_GRASP_ANT_UTILS_H
#define GREEDY_GRASP_ANT_UTILS_H

#include <math.h>
#include <limits.h>

void swap(int *xp, int *yp);
int int_mean(const int* values, int n);
int int_var(const int* values, int n);
int int_std(const int* values, int n);
int int_min(const int* values, int n);
int int_max(const int* values, int n);

#endif //GREEDY_GRASP_ANT_UTILS_H
