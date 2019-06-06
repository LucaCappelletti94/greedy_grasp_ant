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

int dist_tot (int i, data_t *pI)
{
  int j, d;

  d = 0;
  for (j = 1; j <= pI->n; j++)
    d += pI->d[i][j];

  return d;
}

int best_initial_point (data_t *pI)
{
  int i, i_max;
  int d, d_max;

  d_max = -1;
  i_max = -1;
  for (i = 1; i <= pI->n; i++)
  {
    d = dist_tot(i,pI);
    if (d > d_max)
    {
      i_max = i;
      d_max = d;
    }
  }

  return i_max;
}

int dist_from_solution (int i, solution_t *px, data_t *pI)
{
  point q;
  int d;

  d = 0;
  for (q = first_point_in(px); !end_point_list(q,px); q = next_point(q,px))
    d += pI->d[i][get_index(q,px)];

  return d;
}

int best_additional_point (solution_t *px, data_t *pI)
{
  point p;
  int d, d_max;
  int i, i_max;

  d_max = -1;
  i_max = NO_POINT;
  for (p = first_point_out(px); !end_point_list(p,px); p = next_point(p,px))
  {
    i = get_index(p,px);
    d = dist_from_solution(i,px,pI);
    if (d > d_max)
    {
      i_max = i;
      d_max = d;
    }
  }

  return i_max;
}

void greedy (data_t *pI, solution_t *px)
{
  int i;

  while (px->card_x < pI->k)
  {
    i = best_additional_point(px,pI);
    move_point_in(i,px,pI);
  }
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
