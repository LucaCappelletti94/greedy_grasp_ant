#include "greedy.h"

void best_initial_pair (data_t *pI, int *pi_in, int *pj_in)
{
  int i, j;
  int d_max;

  d_max = -1;
  *pi_in = *pj_in = -1;
  for (i = 1; i <= pI->n; i++)
    for (j = i+1; j <= pI->n; j++)
      if (pI->d[i][j] > d_max)
      {
        *pi_in = i;
        *pj_in = j;
        d_max = pI->d[i][j];
      }
}

int idxmax(int** distances, size_t size)
{
  int max=-1, index;
  for (int i=0; i<size; i++)
  {
      if(distances[1][i]>max)
      {
        max = distances[1][i];
        index = distances[0][i];
      }
  }
  return index;
}

int best_initial_point (data_t *pI)
{
  int** distances = initial_distances(pI);
  int best_point = idxmax(distances, pI->n);
  destroy_distances(distances);
  return best_point;
}

int best_additional_point (solution_t *px, data_t *pI)
{
  int n = solution_around_cardinality(px);
  if(n == 0)
    return  NO_POINT;
  int ** distances = additional_distances(px, pI, n);
  int index = idxmax(distances, n);
  destroy_distances(distances);
  return index;
}


void greedy (data_t *pI, solution_t *px)
{
  // While the current solution cardinality is less than the maximum allowed
  // as specified in the input file.
  while (!is_solution_feasible(pI, px))
    move_point_in(best_additional_point(px,pI),px,pI);
}

void greedy_bestsum (data_t *pI, solution_t *px)
{
  int i_in;

  i_in = best_initial_point(pI);
  move_point_in(i_in,px,pI);
  greedy(pI,px);
}

void greedy_bestpair (data_t *pI, solution_t *px)
{
  int i_in, j_in;

  best_initial_pair(pI,&i_in,&j_in);
  move_point_in(i_in,px,pI);
  move_point_in(j_in,px,pI);
  greedy(pI,px);
}

void greedy_tryall (data_t *pI, solution_t *px)
{
  int i_in;
  solution_t x;

  for (i_in = 1; i_in <= pI->n; i_in++)
  {
    create_solution(pI->n,&x);

    move_point_in(i_in,&x,pI);
    greedy(pI,&x);

    if (x.f > px->f) copy_solution(&x,px);
    destroy_solution(&x);
  }
}
