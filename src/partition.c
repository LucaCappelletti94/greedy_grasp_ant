#include "partition.h"

void Scambia (int *pa, int *pb)
{
  int temp;

  temp = *pa;
  *pa = *pb;
  *pb = temp;
}

// NOTA: L'ORDINAMENTO E' DECRESCENTE!
// Riordina un vettore V_val di n int in modo che i primi k siano non inferiori agli ultimi n-k,
// mantenendo allineati agli elementi di V_val quelli del vettore V_ind di interi
// Per ora facciamo l'implementazione banale che porta in cima l'elemento minimo per k volte
// NOTA: per ora ipotizza che sia n > k!!!
void partition_by_card (int n, int *V_val, int *V_ind, int k)
{
  int i, j;

  for (i = 1; i <= k; i++)
    for (j = i+1; j <= n; j++)
      if (V_val[j] > V_val[i])
      {
        Scambia(&V_val[j],&V_val[i]);
        Scambia(&V_ind[j],&V_ind[i]);
      }
}

// NOTA: L'ORDINAMENTO E' DECRESCENTE!
// Riordina un vettore V_val di n int in modo che quelli con la frazione alpha di valori piu' alti
// stiano prima degli altri, mantenendo allineati agli elementi di V_val quelli del vettore V_ind di interi
// NOTA: deve essere 0.0 <= alpha <= 1.0
int partition_by_value (int n, int *V_val, int *V_ind, double alpha)
{
  int i, j;
  int vMin, vMax, vSep; /* valori minimo, massimo e di soglia */

  vMin = INT_MAX;
  vMax = INT_MIN;
  for (i = 1; i <= n; i++)
  {
    if (V_val[i] < vMin) vMin = V_val[i];
    if (V_val[i] > vMax) vMax = V_val[i];
  }

  vSep = vMax - (int) (alpha * (vMax - vMin));

  i = 1; j = n;
  while (i <= j)
    if (V_val[i] >= vSep)
      i++;
    else
    {
      Scambia(&V_val[i],&V_val[j]);
      Scambia(&V_ind[i],&V_ind[j]);
      j--;
    }
    
  return j;
}
