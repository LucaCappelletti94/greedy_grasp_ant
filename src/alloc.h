#ifndef __ALLOC_H
#define __ALLOC_H


#include <stdio.h>
#include <stdlib.h>
#include "defs.h"


// Alloca un vettore di n int
int *int_alloc (int n);

// Alloca una matrice di (n1,n2) int
int **int2_alloc (int n1, int n2);

// Alloca un vettore di n bool
bool *bool_alloc (int n);

#endif /* __ALLOC_H */
