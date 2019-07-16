#ifndef __SOLUTION_H
#define __SOLUTION_H


#include "data.h"

#define NO_POINT -1

typedef struct solution_s
{
  int f;     // valore della soluzione

  int card_x;
  int card_N;

  bool *in_x; // per ogni punto i indica se esso appartiene o no alla soluzione x

  // Liste dei punti nella soluzione x e nel complemento N \setminus x
  int head_x;    // sentinella della lista dei punti in x
  int head_notx; // sentinella della lista dei punti del complemento N \setminus x
  int *next;     // elemento seguente   per ciascun punto
  int *prev;     // elemento precedente per ciascun punto

} solution_t;


// Svuota una soluzione 
void clean_solution (solution_t *px);

// Crea una soluzione vuota per un problema di dimensione n
void create_solution (int n, solution_t *px);

// Dealloca una soluzione puntata da *px
void destroy_solution (solution_t *px);

// Tipi e strutture per accedere ai punti

typedef int point;

// Legge l'indice del punto indicato dal cursore p nella soluzione puntata da *px
int get_index (point p, solution_t *px);

// Determina il punto p di indice i nella soluzione puntata da *px
point get_point (int i, solution_t *px);

// Legge il valore della funzione obiettivo per la soluzione puntata da *px
int get_obj (solution_t *px);

// Indica se si e' arrivati in fondo alla lista (la posizione p e' una sentinella)
bool end_point_list (point p, solution_t *px);

// Indica se la soluzione puntata da *px e' vuota
bool empty_solution (solution_t *px);

// Restituiscono i cursori al primo e all'ultimo punto della soluzione puntata da *px
point first_point_in (solution_t *px);
point last_point_in (solution_t *px);

// Restituiscono i cursori al primo e all'ultimo punto fuori della soluzione puntata da *px
point first_point_out (solution_t *px);
point last_point_out (solution_t *px);

// Restituiscono i cursori al punto che segue e a quello che precede il punto individuato dal cursore p
point next_point (point p, solution_t *px);
point prev_point (point p, solution_t *px);

// Aggiunge il punto di indice i alla soluzione puntata da *px
void move_point_in (int i, solution_t *px, data_t *pI);

// Cancella il punto di indice i dalla soluzione puntata da *px
void move_point_out (int i, solution_t *px, data_t *pI);

// Calcola il costo di una soluzione puntata da *px in base ai punti che la compongono e ai dati dell'istanza *pI
void compute_obj (solution_t *px, data_t *pI);

// Copia la soluzione puntata da *px_orig nella soluzione puntata da *px_dest
void copy_solution (solution_t *px_orig, solution_t *px_dest);

// Verifica la coerenza interna della soluzione puntata da *px in base
// all'istanza puntata da *pI, partendo dal vettore di incidenza
bool check_solution (solution_t *px, data_t *pI);

// Copia in un vettore di interi gli elementi che appartengono alla soluzione
//void dump_soluzione(lista_nodi_t *lista_nodi, soluzione_t * soluzione_dest);

// Recupera in lista_nodi la soluzione salvata in soluzione
//void retrieve_soluzione(matrice_distanze_t *matrice_distanze, soluzione_t *soluzione, lista_nodi_t *lista_nodi);

// Stampa la soluzione puntata da *px
void print_solution (solution_t *px);

int solution_around_cardinality(solution_t *px);

bool is_solution_feasible(data_t *pI, solution_t *px);

#endif /* __SOLUTION_H */
