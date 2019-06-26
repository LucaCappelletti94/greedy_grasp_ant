//
// Created by Luca Cappelletti on 2019-06-25.
//

#ifndef GREEDY_GRASP_ANT_DISTRIBUTIONS_H
#define GREEDY_GRASP_ANT_DISTRIBUTIONS_H

#include "defs.h"
#include "math.h"
#include "distances.h"

int choice(const double* p, size_t n);
double* uniform(int** distances, size_t n, size_t max);
double* linear_HBSS(int** distances, size_t n, size_t max);
double* exponential_HBSS(int** distances, size_t n, size_t max);
double* linear_RCL(int** distances, size_t n, size_t max);
double* exponential_RCL(int** distances, size_t n, size_t max);
int random_index(int** distances, double* distribution, size_t n);

#endif //GREEDY_GRASP_ANT_DISTRIBUTIONS_H
