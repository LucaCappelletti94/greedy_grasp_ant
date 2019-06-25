#ifndef __GREEDY_H
#define __GREEDY_H


#include "data.h"
#include "solution.h"
#include "distances.h"

int dist_from_solution (int i, solution_t *px, data_t *pI);

void greedy_bestsum (data_t *pI, solution_t *px);

void greedy_bestpair (data_t *pI, solution_t *px);

void greedy_tryall (data_t *pI, solution_t *px);

void greedy (data_t *pI, solution_t *px);

#endif /* __GREEDY_H */
