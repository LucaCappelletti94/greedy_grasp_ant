#ifndef __DATA_H
#define __DATA_H


#include "defs.h"
#include "alloc.h"


typedef struct data_s
 {
  int n;   // cardinalita' dell'insieme N dei punti
  int k;   // cardinalita' delle soluzioni ammissibili x \in X
  int **d; // matrice delle distanze fra punti (simmetrica)
 } data_t;


// Carica dal file data_file i dati dell'istanza puntata da *pI
void load_data (char *data_file, data_t *I);

// Dealloca le strutture dell'istanza puntata da *pI
void destroy_data (data_t *I);

// Stampa l'istanza puntata da *pI
void print_data (data_t *I);


#endif /* __DATA_H */
