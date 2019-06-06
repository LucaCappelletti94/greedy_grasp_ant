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

  // Riordina d e ind portando in testa i valori piu' grandi
  num = partition_by_value(tot,d,ind,alpha);

  // Sceglie uno dei candidati
  i_max = ind[rand_int(1,num,pidum)];

  free(d);
  free(ind);
  return i_max;
}

void semigreedy (data_t *pI, solution_t *px, double alpha, int iterTot, long *pidum)
{
  int i;

  while (px->card_x < pI->k)
  {
    i = best_random_additional_point(px,pI,alpha,pidum);
    move_point_in(i,px,pI);
  }
}
