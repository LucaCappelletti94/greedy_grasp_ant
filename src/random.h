#ifndef _ran1_h
#define _ran1_h

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)


double ran1 (long *idum);

/* Estrae un intero casuale fra iMin e iMax (compresi) con probabilita' uniforme */
int rand_int (int iMin, int iMax, long* idum);

/* Estrae un indice casuale fra iMin e iMax (compresi) con probabilita' data dagli elementi del vettore P */
int rand_index (int iMin, int iMax, double *P, long *seed);

/* Genera e assegna al vettore intero v dall'indice s all'indice e valori casuali uniformi fra v_min e v_max */
void generate_random_int_vector (int *v, int s, int e, int v_min, int v_max, long *pseed);

/* Permuta casualmente i valori del vettore intero v dall'indice s all'indice e */
void permute_int_vector (int *v, int s, int e, long *pseed);

#endif
