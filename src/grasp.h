//
// Created by Luca Cappelletti on 2019-06-25.
//

#ifndef GREEDY_GRASP_ANT_GRASP_H
#define GREEDY_GRASP_ANT_GRASP_H

#include "distributions.h"

void parametrized_uniform_grasp(data_t *pI, solution_t *px);
void parametrized_linear_HBSS_grasp(data_t *pI, solution_t *px);
void parametrized_exponential_HBSS_grasp(data_t *pI, solution_t *px);
void parametrized_uniform_RCL_grasp(data_t *pI, solution_t *px);
void parametrized_linear_RCL_grasp(data_t *pI, solution_t *px);
void parametrized_exponential_RCL_grasp(data_t *pI, solution_t *px);

#endif //GREEDY_GRASP_ANT_GRASP_H
