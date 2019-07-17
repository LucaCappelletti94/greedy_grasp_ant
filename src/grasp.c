//
// Created by Luca Cappelletti on 2019-06-25.
//

#include "grasp.h"

int random_point(int** distances, int n, size_t max, double* (*get_distribution)(int**, size_t, size_t))
{
  double* distribution = get_distribution(distances, n, max);
  int index = random_index(distances, distribution, n);
  free(distribution);
  return index;
}

int random_additional_point (solution_t *px, data_t *pI, size_t max, double* (*get_distribution)(int**, size_t, size_t))
{
  int n = solution_around_cardinality(px);
  if(n == 0)
    return  NO_POINT;
  int ** distances = additional_distances(px, pI, n);
  int index = random_point(distances, n, max, get_distribution);
  destroy_distances(distances);
  return index;
}

void grasp(data_t *pI, solution_t *px, int iterations, size_t max, double* (*get_distribution)(int**, size_t, size_t))
{
  solution_t best;
  create_solution(px->card_N, &best);
  for(int i=1; i<=iterations; i++) {
    // While the current solution cardinality is less than the maximum allowed
    // as specified in the input file.
    while (!is_solution_feasible(pI, px))
      move_point_in(random_additional_point(px, pI, max, get_distribution), px, pI);
    if (best.f < px->f) {
      copy_solution(px, &best);
      clean_solution(px);
    }
  }
  copy_solution(&best, px);
}

void uniform_RCL_grasp(data_t *pI, solution_t *px, int iterations, size_t max)
{
  grasp(pI, px, iterations, max, uniform_RCL);
}

void linear_RCL_grasp(data_t *pI, solution_t *px, int iterations, size_t max)
{
  grasp(pI, px, iterations, max, linear_RCL);
}

void exponential_RCL_grasp(data_t *pI, solution_t *px, int iterations, size_t max)
{
  grasp(pI, px, iterations, max, exponential_RCL);
}

void uniform_grasp(data_t *pI, solution_t *px, int iterations)
{
  uniform_RCL_grasp(pI, px, iterations, solution_around_cardinality(px));
}

void linear_HBSS_grasp(data_t *pI, solution_t *px, int iterations)
{
  linear_RCL_grasp(pI, px, iterations, solution_around_cardinality(px));
}

void exponential_HBSS_grasp(data_t *pI, solution_t *px, int iterations)
{
  exponential_RCL_grasp(pI, px, iterations, solution_around_cardinality(px));
}