#ifndef __PARTITION_H
#define __PARTITION_H


#include <stdio.h>
#include <stdlib.h>


// Riordina un vettore V_val di n int in modo che i primi k siano non superiori agli ultimi n-k,
// mantenendo allineati agli elementi di V_val quelli del vettore V_ind di interi
// Per ora facciamo l'implementazione banale che porta in cima l'elemento minimo per k volte
// NOTA: per ora ipotizza che sia n > k!!!
void partition_by_card (int n, int *V_val, int *V_ind, int k);

// Riordina un vettore V_val di n int in modo che quelli con la frazione alpha di valori piu' bassi
// stiano prima degli altri, mantenendo allineati agli elementi di V_val quelli del vettore V_ind di interi
// Restituisce l'indice terminale della prima parte dei vettori
// NOTA: deve essere 0.0 <= alpha <= 1.0
int partition_by_value (int n, int *V_val, int *V_ind, double alpha);

#endif /* __PARTITION_H */
