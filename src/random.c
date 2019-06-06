#include "random.h"

double ran1 (long *idum)
{
  int j;
  long k;
  static long iy = 0;
  static long iv[NTAB];

  if (*idum <= 0 || !iy)
  { if (-(*idum) < 1)
      *idum = 1;
    else
      *idum = -(*idum);
    for (j = NTAB+7; j >= 0; j--)
    { k = (*idum)/IQ;
      *idum = IA*(*idum-k*IQ) - IR*k;
      if (*idum < 0) *idum += IM;
      if (j < NTAB) iv[j] = *idum;
    }
    iy = iv[0];
  }
  k = (*idum)/IQ;
  *idum = IA*(*idum-k*IQ) - IR*k;
  if (*idum <  0) *idum += IM;
  j = iy/NDIV;
  iy = iv[j];
  iv[j] = *idum;
  if (AM*iy > RNMX)
    return RNMX;
  else
    return AM*iy;
}


/* Estrae un intero casuale fra iMin e iMax (compresi) con probabilita' uniforme */
int rand_int (int iMin, int iMax, long* idum)
{
  return iMin + (int) (ran1(idum) * (iMax-iMin+1-EPS));
}


/* Estrae un indice casuale fra iMin e iMax (compresi) con probabilita' proporzionali agli elementi del vettore P. */
int rand_index (int iMin, int iMax, double *P, long *pseed)
{
  double r, rTot, sumP;
  int i;


  sumP = 0.0;
  for (i = iMin; i <= iMax; i++)
    sumP += P[i];

  r = ran1(pseed) * sumP;
  i = iMin;
  rTot = P[iMin];
  while ( (r > rTot) && (i <= iMax) )
  {
    i++;
    rTot += P[i];
  }

  return i;
}

/* Genera e assegna al vettore intero v dall'indice s all'indice e valori casuali uniformi fra v_min e v_max */
void generate_random_int_vector (int *v, int s, int e, int v_min, int v_max, long *pseed)
{
  int i;

  for (i = s; i <= e; i++)
    v[i] = v_min + (int) (ran1(pseed) * (v_max - v_min - EPS));
}

/* Permuta casualmente i valori del vettore intero v dall'indice s all'indice e */
void permute_int_vector (int *v, int s, int e, long *pseed)
{
  int i, ii, temp;

  for (i = s; i < e; i++)
  {
    ii = rand_int(i+1,e,pseed);
    temp = v[i];
    v[i] = v[ii];
    v[ii] = temp;
  }
}
