#include "solution.h"

// Svuota una soluzione 
void clean_solution (solution_t *px)
{
  int p;

  px->f = 0;

  px->card_x = 0;

  // La soluzione contiene solo la sentinella
  px->head_x = 0;
  px->prev[0] = px->next[0] = 0;

  // Il complemento contiene tutti i punti, ordinati per indici crescenti
  px->head_notx = px->card_N+1;
  for (p = 1; p <= px->card_N; p++)
  {
    px->in_x[p] = false;
    px->prev[p+1] = p;
    px->next[p] = p+1;
  }
  px->prev[1] = px->card_N+1;
  px->next[px->card_N+1] = 1;
}

// Crea una soluzione vuota per un problema di dimensione n
void create_solution (int n, solution_t *px)
{
  px->card_N = n;

  px->in_x = bool_alloc(n+1);

  // Liste dei punti nella soluzione x e nel complemento N \setminus x
  px->next = int_alloc(n+1+1);
  px->prev = int_alloc(n+1+1);

  clean_solution(px);
}

// Dealloca la soluzione puntata da *px
void destroy_solution (solution_t *px)
{
  px->f = 0;

  px->card_x = px->card_N = 0;

  free(px->in_x);
  px->in_x = NULL;

  px->head_x = 0;
  px->head_notx = 0;
  free(px->next);
  px->next = NULL;
  free(px->prev);
  px->prev = NULL;
}

// Determina l'indice del punto indicato dal cursore p nella soluzione puntata da *px
int get_index (point p, solution_t *px)
{
  return (int) p;
}

// Determina il punto p di indice i nella soluzione puntata da *px
point get_point (int i, solution_t *px)
{
  return (point) i;
}

// Legge il valore della funzione obiettivo per la soluzione puntata da *px
int get_obj (solution_t *px)
{
  return px->f;
}

// Indica se si e' arrivati in fondo alla lista (la posizione p e' una sentinella)
bool end_point_list (point p, solution_t *px)
{
  return ( (p < 1) || (p > px->card_N) );
}

// Indica se la soluzione puntata da *px e' vuota
bool empty_solution (solution_t *px)
{
  return (px->next[px->head_x] == px->head_x);
}

// Restituiscono i cursori al primo e all'ultimo punto della soluzione puntata da *px
point first_point_in (solution_t *px)
{
  return px->next[px->head_x];
}

point last_point_in (solution_t *px)
{
  return px->prev[px->head_x];
}

// Restituiscono i cursori al primo e all'ultimo punto fuori della soluzione puntata da *px
point first_point_out (solution_t *px)
{
  return px->next[px->head_notx];
}

point last_point_out (solution_t *px)
{
  return px->prev[px->head_notx];
}

// Restituiscono i cursori al punto che segue e a quello che precede il punto individuato dal cursore p
point next_point (point p, solution_t *px)
{
  return px->next[p];
}

point prev_point (point p, solution_t *px)
{
  return px->prev[p];
}

// Aggiunge il punto di indice i alla soluzione puntata da *px
void move_point_in (int i, solution_t *px, data_t *pI)
{
  point pp, sp, p;

  if (px->in_x[i] == true)
  {
    fprintf(stderr,"Point %d is already in the solution!\n",i);
    exit(EXIT_FAILURE);
  }
  else
  {
    // Cancella il punto dalla lista corrente
    sp = px->next[i];
    pp = px->prev[i];
    px->next[pp] = sp;
    px->prev[sp] = pp;

    // Aggiunge il punto nell'altra lista
    sp = px->next[px->head_x];
    pp = px->head_x;
    px->next[i] = sp;
    px->prev[i] = pp;
    px->next[pp] = i;
    px->prev[sp] = i;

    // Aggiorna la cardinalita'
    px->card_x++;

    // Aggiorna il vettore di incidenza
    px->in_x[i] = true;

    // Aggiorna il valore dell'obiettivo
    for (p = first_point_in(px); !end_point_list(p,px); p = next_point(p,px))
      px->f += pI->d[get_index(p,px)][i];
  }
}

// Cancella il punto di indice i dalla soluzione puntata da *px
void move_point_out (int i, solution_t *px, data_t *pI)
{
  point pp, sp, p;

  if (px->in_x[i] == false)
  {
    fprintf(stderr,"Point %d is already out of the solution!\n",i);
    exit(EXIT_FAILURE);
  }
  else
  {
    // Cancella il punto dalla lista corrente
    sp = px->next[i];
    pp = px->prev[i];
    px->next[pp] = sp;
    px->prev[sp] = pp;

    // Aggiunge il punto nell'altra lista
    sp = px->next[px->head_notx];
    pp = px->head_notx;
    px->next[i] = sp;
    px->prev[i] = pp;
    px->next[pp] = i;
    px->prev[sp] = i;

    // Aggiorna la cardinalita'
    px->card_x--;

    // Aggiorna il vettore di incidenza
    px->in_x[i] = false;

    // Aggiorna il valore dell'obiettivo
    for (p = first_point_in(px); !end_point_list(p,px); p = next_point(p,px))
      px->f -= pI->d[get_index(p,px)][i];
  }
}

// Calcola il costo di una soluzione in base ai punti che la compongono
void compute_obj (solution_t *px, data_t *pI)
{
  point p, q;

  px->f = 0;
  for (p = first_point_in(px); !end_point_list(p,px); p = next_point(p,px))
    for (q = first_point_in(px); !end_point_list(q,px); q = next_point(q,px))
      px->f += pI->d[get_index(p,px)][get_index(q,px)];
}

// Copia la soluzione puntata da *px_orig nella soluzione puntata da *px_dest
void copy_solution (solution_t *px_orig, solution_t *px_dest)
{
  int i;

  px_dest->f = px_orig->f;

  px_dest->card_x = px_orig->card_x;
  px_dest->card_N = px_orig->card_N;

  for (i = 0; i <= px_dest->card_N; i++)
    px_dest->in_x[i] = px_orig->in_x[i];

  px_dest->head_x = px_orig->head_x;
  px_dest->head_notx = px_orig->head_notx;

  for (i = 0; i <= px_dest->card_N+1; i++)
  {
    px_dest->next[i] = px_orig->next[i];
    px_dest->prev[i] = px_orig->prev[i];
  }
}

// Verifica la coerenza interna della soluzione puntata da *px in base
// all'istanza puntata da *pI, partendo dal vettore di incidenza
bool check_solution (solution_t *px, data_t *pI)
{
  int i, j;
  int ff, cont;
  point p;

  ff = 0;
  for (i = 1; i <= px->card_N; i++)
    if (px->in_x[i] == true)
      for (j = i+1; j <= px->card_N; j++)
        if (px->in_x[j] == true)
          ff += pI->d[i][j];

  if (ff != px->f) return false;

  cont = 0;
  for (p = first_point_in(px); !end_point_list(p,px); p = next_point(p,px))
  {
    if (px->in_x[get_index(p,px)] == false) return false;
    cont++;
  }
  if (cont != px->card_x) return false;

  cont = 0;
  for (p = first_point_out(px); !end_point_list(p,px); p = next_point(p,px))
  {
    if (px->in_x[get_index(p,px)] == true) return false;
    cont++;
  }
  if (cont != px->card_N-px->card_x) return false;

  return true;
}

// Stampa la soluzione puntata da *px
void print_solution (solution_t *px)
{
  point p;

  printf("%6d ",get_obj(px));
  for (p = first_point_in(px); !end_point_list(p,px); p = next_point(p,px))
    printf("%4d ",get_index(p,px));
}

/*
// Copia in un vettore di interi gli elementi che appartengono alla soluzione
void dump_soluzione(lista_nodi_t *lista_nodi, soluzione_t * soluzione_dest)
{
 int i, pos=0;
 //soluzione_dest->elemento_m = (int *) calloc(m, sizeof(int));

 soluzione_dest->Z = lista_nodi->Z;
 for(i = lista_nodi->M_head ; i != (unsigned) CURSORE_NULL ; i = lista_nodi->nodo[i].next)
 {
  soluzione_dest->elemento_m[pos]=i;
  ++pos;
 }
}

// Recupera in lista_nodi la soluzione salvata in soluzione
void retrieve_soluzione(matrice_distanze_t *matrice_distanze, soluzione_t *soluzione, lista_nodi_t *lista_nodi)
{
  int i;

  carica_lista_nodi(matrice_distanze,lista_nodi);
  for (i = 0; i < matrice_distanze->m; i++)
    aggiungi_nodo_lista_nodi_soluzione(soluzione->elemento_m[i],matrice_distanze,lista_nodi);
  lista_nodi->Z = soluzione->Z;
}
*/
