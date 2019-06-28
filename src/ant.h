//
// Created by Luca Cappelletti on 2019-06-25.
//

#ifndef GREEDY_GRASP_ANT_ANT_H
#define GREEDY_GRASP_ANT_ANT_H
#include "solution.h"
#include "distributions.h"
#include <math.h>

void ant_system(data_t *pI, solution_t *px, int iterations, double oblivion, double mu_memory, double mu_data);
void parametrized_ant_system(data_t *d, solution_t *x);

#endif //GREEDY_GRASP_ANT_ANT_H
