//
// Created by Luca Cappelletti on 2019-06-25.
//

#include "grasp.h"

int random_index(int** distances, int n, size_t max, float* (*get_distribution)(int**, size_t, size_t))
{
  float* distribution = get_distribution(distances, n, max);
  int position = choice(distribution, n);
  free(distribution);
  return distances[0][position];
}

int random_initial_point (data_t *pI, size_t max, float* (*get_distribution)(int**, size_t, size_t))
{
  int** distances = initial_distances(pI);
  int index = random_index(distances, pI->n, max, get_distribution);
  destroy_distances(distances);
  return index;
}

int random_additional_point (solution_t *px, data_t *pI, size_t max, float* (*get_distribution)(int**, size_t, size_t))
{
  int n = solution_around_cardinality(px);
  if(n == 0)
    return  NO_POINT;
  int ** distances = additional_distances(px, pI, n);
  int index = random_index(distances, n, max, get_distribution);
  destroy_distances(distances);
  return index;
}

void grasp(data_t *pI, solution_t *px, size_t max, float* (*get_distribution)(int**, size_t, size_t))
{
  int i;
  // While the current solution cardinality is less than the maximum allowed
  // as specified in the input file.
  while (px->card_x < pI->k)
  {
    // Determine the new best additional point following the current algorithm score function
    i = random_additional_point(px, pI, max, get_distribution);
    move_point_in(i,px,pI);
  }
}

void uniform_grasp(data_t *pI, solution_t *px)
{
  grasp(pI, px, 0, uniform);
}

void linear_HBSS_grasp(data_t *pI, solution_t *px)
{
  grasp(pI, px, 0, linear_HBSS);
}

void exponential_HBSS_grasp(data_t *pI, solution_t *px)
{
  grasp(pI, px, 0, exponential_HBSS);
}

void linear_RCL_grasp(data_t *pI, solution_t *px, size_t max)
{
  grasp(pI, px, max, linear_RCL);
}

void exponential_RCL_grasp(data_t *pI, solution_t *px, size_t max)
{
  grasp(pI, px, max, exponential_RCL);
}