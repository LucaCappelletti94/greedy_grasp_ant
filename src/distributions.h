//
// Created by Luca Cappelletti on 2019-06-25.
//

#ifndef GREEDY_GRASP_ANT_DISTRIBUTIONS_H
#define GREEDY_GRASP_ANT_DISTRIBUTIONS_H

#include "defs.h"
#include "math.h"
#include "distances.h"

int choice(const float* p, size_t n);
float* uniform(int** distances, size_t n, size_t max);
float* linear_HBSS(int** distances, size_t n, size_t max);
float* exponential_HBSS(int** distances, size_t n, size_t max);
float* linear_RCL(int** distances, size_t n, size_t max);
float* exponential_RCL(int** distances, size_t n, size_t max);

#endif //GREEDY_GRASP_ANT_DISTRIBUTIONS_H
