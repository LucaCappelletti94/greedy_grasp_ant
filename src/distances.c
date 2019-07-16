//
// Created by Luca Cappelletti on 2019-06-25.
//

#include "distances.h"
#include "utils.h"

//
// The distances are represented by two integer arrays with length n.
// The first array contains the index of the given point.
// The second array contains the distance of the given point from the given solution.
//

int** alloc_distances(size_t n)
{
  int** distances = pint_alloc(2);
  for (int i=0; i<2; i++)
    distances[i] = int_alloc(n);
  return distances;
}

void destroy_distances(int** distances)
{
  free(distances[0]);
  free(distances[1]);
  free(distances);
}

void print_distances(int** distances, size_t n)
{
  printf("[\n");
  for(int i=0; i<n; i++)
  {
    printf("\t(%d, %d), ", distances[0][i], distances[1][i]);
  }
  printf("]\n");
}

int point_distance (int point_index, data_t *pI)
{
  int d = 0;
  for (int j = 1; j <= pI->n; d += pI->d[point_index][j], j++);
  return d;
}

// Order the distances from greater to smaller.
void sort_distances(int** distances, int n)
{
  int i, j;
  for (i = 0; i < n-1; i++)
    for (j = 0; j < n-i-1; j++)
      if (distances[1][j] < distances[1][j+1]){
        swap(&distances[1][j], &distances[1][j+1]);
        swap(&distances[0][j], &distances[0][j+1]);
      }

}

int** initial_distances(data_t *pI)
{
  int** distances = alloc_distances(pI->n);
  for (int i = 1; i <= pI->n; i++)
  {
    distances[0][i]=i;
    distances[1][i]=point_distance(i,pI);
  }
  return distances;
}

// Determines the distance of the new point from the ones already in the solution as the sum of all the distances.
// Since this sum is then compared to other sums from the same solution, there's no need to divide it by the number of points.
int point_distance_from_solution (int i, solution_t *px, data_t *pI)
{
  int d = 0;
  for (point q = first_point_in(px); !end_point_list(q,px);  d += pI->d[i][get_index(q,px)], q = next_point(q,px));
  return d;
}

int** additional_distances(solution_t *px, data_t *pI, size_t cardinality)
{
  point p;
  int i, j;
  int** distances = alloc_distances(cardinality);
  for (p = first_point_out(px), i=0; !end_point_list(p,px); p = next_point(p,px), i++)
  {
    j = get_index(p,px);
    distances[0][i]=j;
    distances[1][i]=point_distance_from_solution(j,px,pI);
  }
  return distances;
}