#include "greedy.h"
#include "random.h"
#include "partition.h"


int best_random_additional_point (solution_t *px, data_t *pI, double alpha, long *pidum)
{
  point p;
  int *d;
  int i, i_max;
  int *ind;
  int num, tot;


  d = int_alloc(pI->n+1);
  ind = int_alloc(pI->n+1);

  tot = 0;
  for (p = first_point_out(px); !end_point_list(p,px); p = next_point(p,px))
  {
    tot++;
    i = get_index(p,px);
    d[tot] = dist_from_solution(i,px,pI);
    ind[tot] = i;
  }

  // Riordinare d e ind portando in testa i valori piu' grandi
  num = partition_by_value(tot,d,ind,alpha);

  // Scegliere uno dei candidati
  i_max = ind[rand_int(1,num,pidum)];

  free(d);
  free(ind);
  return i_max;
}

void semigreedy (data_t *pI, solution_t *px, double alpha, int iterTot, long *pidum)
{
  int i, iter;
  solution_t xCurr;

  create_solution(pI->n,&xCurr);
  copy_solution(px,&xCurr);
  for (iter = 1; iter <= iterTot; iter++)
  {
    while (xCurr.card_x < pI->k)
    {
      i = best_random_additional_point(&xCurr,pI,alpha,pidum);
      move_point_in(i,&xCurr,pI);
    }
    print_solution(&xCurr);
    printf("\n");
    if (xCurr.f  > px->f) copy_solution(&xCurr,px);
    clean_solution(&xCurr);
  }
  destroy_solution(&xCurr);
}
