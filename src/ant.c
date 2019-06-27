//
// Created by Luca Cappelletti on 2019-06-25.
//

#include "ant.h"

double maximization_visibility(int score)
{
  return (double) score;
}

double minimization_visibility(int score)
{
  return 1.0/ maximization_visibility(score);
}

void update_trace(solution_t *Y, double oblivion, double* trace, size_t n)
{
  for(int i=0; i<n; i++)
    if(Y->in_x[i])
      trace[i] = (1-oblivion)*trace[i] + oblivion*Y->f;
}

double* init_trace(size_t n){
  double* trace = double_alloc(n);
  for(int i=0; i<n; trace[i]=1.0, i++);
  return trace;
}

double* ant_distribution(int** distances, double* trace, double mu_memory, double mu_data, size_t n, double (*visibility)(int))
{
  double* distribution = double_alloc(n);
  double denominator = 0;
  for(int i=0; i<n; i++)
  {
    distribution[i] = pow(visibility(distances[1][i]), mu_data)*pow(trace[distances[0][i]], mu_memory);
    denominator += distribution[i];
  }
  for(int i=0; i<n;  distribution[i]/=denominator, i++);
  return distribution;
}

int random_ant_point(int** distances, double* trace, double mu_memory, double mu_data, size_t n)
{
  double * distribution = ant_distribution(distances, trace, mu_memory, mu_data, n, maximization_visibility);
  int index = random_index(distances, distribution, n);
  free(distribution);
  return index;
}

int ant_additional_point (solution_t *px, data_t *pI, double* trace, double mu_memory, double mu_data)
{
  int n = solution_around_cardinality(px);
  if(n == 0)
    return  NO_POINT;
  int ** distances = additional_distances(px, pI, n);
  int index = random_ant_point(distances, trace, mu_memory, mu_data, n);
  destroy_distances(distances);
  return index;
}

void ant_system(data_t *pI, solution_t *px, int iterations, double oblivion, double mu_memory, double mu_data)
{
  double* trace = init_trace(pI->n);
  for(int i=1; i<=iterations; i++){
    // While the current solution cardinality is less than the maximum allowed
    // as specified in the input file.
    while (px->card_x < pI->k)
      move_point_in(ant_additional_point(px, pI, trace, mu_memory, mu_data), px, pI);
    update_trace(px, oblivion, trace, pI->n);
    if(i!=iterations)
      clean_solution(px);
  }
  free(trace);
}