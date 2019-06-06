#include "alloc.h"

// Alloca un vettore di n int
int *int_alloc (int n)
{
  int *v = (int *) calloc(n,sizeof(int));
  if (v == NULL)
  {
    fprintf(stderr,"Not enough memory to allocate a vector of %d int!",n);
    exit(EXIT_FAILURE);
  }
  return v;
}

// Alloca un vettore di n int*
int **pint_alloc (int n)
{
  int **v = (int **) calloc(n,sizeof(int *));
  if (v == NULL)
  {
    fprintf(stderr,"Not enough memory to allocate a vector of %d int*!",n);
    exit(EXIT_FAILURE);
  }
  return v;
}

// Alloca una matrice di (n1,n2) int
int **int2_alloc (int n1, int n2)
{
  int i, **m = pint_alloc(n1);
  for (i = 0; i < n1; i++)
    m[i] = int_alloc(n2);
  return m;
}

// Alloca un vettore di n bool
bool *bool_alloc (int n)
{
  bool *v = (bool *) calloc(n,sizeof(bool));
  if (v == NULL)
  {
    fprintf(stderr,"Not enough memory to allocate a vector of %d bool!",n);
    exit(EXIT_FAILURE);
  }
  return v;
}
