//
// Created by Luca Cappelletti on 2019-06-25.
//

#ifndef GREEDY_GRASP_ANT_DISTANCES_H
#define GREEDY_GRASP_ANT_DISTANCES_H

#include "stdlib.h"
#include "stdio.h"
#include "data.h"
#include "solution.h"

int** alloc_distances(size_t n);
void destroy_distances(int** distances);
void print_distances(int** distances, size_t n);
int point_distance (int point_index, data_t *pI);
int** initial_distances(data_t *pI);
int** additional_distances(solution_t *px, data_t *pI, size_t cardinality);
void sort_distances(int** distances, int n);


#endif //GREEDY_GRASP_ANT_DISTANCES_H
