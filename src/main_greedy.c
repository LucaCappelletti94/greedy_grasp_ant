#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "greedy.h"
#include "localsearch.h"


void parse_command_line (int argc, char *argv[], char *data_file, char *param, double *palpha, int *piterTot, long *pseme);


int main (int argc, char *argv[])
{
  char data_file[NAME_LENGTH];
  data_t I;
  solution_t x;
  char param[NAME_LENGTH];
  double alpha;
  int iterTot;
  long seme;
  time_t inizio, fine;
  double tempo;


  parse_command_line(argc,argv,data_file,param,&alpha,&iterTot,&seme);

  load_data(data_file,&I);
  //print_data(&I);

  create_solution(I.n,&x);

  inizio = clock();
  if (strcmp(param,"-g") == 0)
    greedy(&I,&x);
  else if (strcmp(param,"-gbs") == 0)
    greedy_bestsum(&I,&x);
  else if (strcmp(param,"-gbp") == 0)
    greedy_bestpair(&I,&x);
  else if (strcmp(param,"-gta") == 0)
    greedy_tryall(&I,&x);
  else if (strcmp(param,"-sg") == 0)
    semigreedy(&I,&x,alpha,iterTot,&seme);
  fine = clock();
  tempo = (double) (fine - inizio) / CLOCKS_PER_SEC;

  printf("%s ",data_file);
  printf("%10.6lf ",tempo);
  print_solution(&x);
  printf("\n");

  destroy_solution(&x);
  destroy_data(&I);

  return EXIT_SUCCESS;
}


void print_usage (char *command)
{
  fprintf(stderr,"Use: %s [datafile] [-g|-gbs|-gbp|-gta|-sg]\n",command);
  fprintf(stderr,"datafile:       name and path of data file\n");
  fprintf(stderr,"-g:             basic greedy heuristic\n");
  fprintf(stderr,"-gbs:           greedy heuristic starting from point with the largest distance sum\n");
  fprintf(stderr,"-gbp:           greedy heuristic starting from two farthest points\n");
  fprintf(stderr,"-gta:           greedy heuristic starting from each point\n");
  fprintf(stderr,"-sg alpha seed: semigreedy heuristic\n");
}


void parse_command_line (int argc, char *argv[], char *data_file, char *param, double *palpha, int *piterTot, long *pseme)
{
  if ( (argc < 2) || (argc > 6) )
  {
    print_usage(argv[0]);
    exit(EXIT_FAILURE);
  }

  strcpy(data_file,argv[1]);
  strcpy(param,"-g");
  if (argc >= 3)
  {
    if ( (strcmp(argv[2],"-g") != 0) && (strcmp(argv[2],"-gbs") != 0) &&
         (strcmp(argv[2],"-gbp") != 0) && (strcmp(argv[2],"-gta") != 0) &&
         (strcmp(argv[2],"-sg") != 0) )
    {
      print_usage(argv[0]);
      exit(EXIT_FAILURE);
    }
    strcpy(param,argv[2]);
    if (strcmp(argv[2],"-sg") == 0) 
    {   
      if (argc != 6)
      {
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
      }
      sscanf(argv[3],"%lf",palpha);
      sscanf(argv[4],"%d",piterTot);
      sscanf(argv[5],"%ld",pseme);
    }
  }
}
