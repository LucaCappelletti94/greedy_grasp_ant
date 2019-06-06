#include "data.h"

// Cerca la stringa s nel file aperto puntato da fp;
// se Rewind = true, riparte dal principio del file.
bool find_token (FILE *fp, char *s, bool Rewind)
{
  char s2[NAME_LENGTH];

  if (Rewind == true) rewind(fp);
  while (fscanf(fp,"%s",s2) != EOF)
  {
    if (strcmp(s,s2) == 0) return true;
  }
  return false;
}

// Carica dal file data_file i dati dell'istanza puntata da pI
void load_data (char *data_file, data_t *pI)
{
  FILE *fp;
  int i, j, ii, jj, d;
  char s[NAME_LENGTH];


  fp = fopen(data_file,"r");
  if (fp == NULL)
  {
    fprintf(stderr,"File %s could not be opened!\n",data_file);
    exit(EXIT_FAILURE);
  }

  if (find_token(fp,"n",true) == false)
  {
    fprintf(stderr,"File %s does not provide n!\n",data_file);
    exit(EXIT_FAILURE);
  }
  fscanf(fp,"%*s %d",&pI->n);
  pI->d = int2_alloc(pI->n+1,pI->n+1);

  if (find_token(fp,"m",true) == false)
  {
    fprintf(stderr,"File %s does not provide k!\n",data_file);
    exit(EXIT_FAILURE);
  }
  fscanf(fp,"%*s %d",&pI->k);

  if (find_token(fp,"D",true) == false)
  {
    fprintf(stderr,"File %s does not provide D!\n",data_file);
    exit(EXIT_FAILURE);
  }
  fscanf(fp,"%*s");
  for (ii = 1; ii <= pI->n; ii++)
    for (jj = 1; jj <= pI->n; jj++)
    {
      fscanf(fp,"%s",s);
      sscanf(s,"[%d,%d]",&i,&j);
      fscanf(fp," %d",&d);
      pI->d[i][j] = d;
    }
}

// Dealloca le strutture dell'istanza puntata da pI
void destroy_data (data_t *pI)
{
  int i;

  for (i = 0; i < pI->n; i++)
    free(pI->d[i]);
  free(pI->d);
  pI->d = NULL;
  pI->n = pI->k = 0;
}


// Stampa l'istanza puntata da pI
void print_data (data_t *pI)
{
  int i, j;

  printf("param n := %d ;\n\n",pI->n);
  printf("param m := %d ;\n\n",pI->k);
  printf("param D :=\n");
  for (i = 1; i <= pI->n; i++)
  {
    for (j = 1; j <= pI->n; j++)
      printf("[%d,%d] %d ",i,j,pI->d[i][j]);
    printf("\n");
  }
  printf(";\n\n");
  printf("end;\n");
}
