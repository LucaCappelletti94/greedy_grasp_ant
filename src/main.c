#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "greedy.h"
#include "grasp.h"
#include "ant.h"


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

  //parse_command_line(argc,argv,data_file,param,&alpha,&iterTot,&seme);
  strcpy(data_file,argv[1]);
  double oblivion = strtod(argv[2], NULL);
  double memory_mu = strtod(argv[3], NULL);
  double data_mu = strtod(argv[4], NULL);
  FILE *f = fopen("tmp.csv", "w");
  fprintf(f, "Heuristic,Score\n");

  printf("Data file: %s\n",data_file);
  load_data(data_file,&I);

  int cardinality = 10;
  int seeds = 10;

  printf("Scores:\n");
  inizio = clock();
  create_solution(I.n,&x);
  /*greedy(&I,&x);
  printf("\tGreedy: %d\n", x.f);
  fprintf(f, "Greedy,%d\n", x.f);
  clean_solution(&x);
  greedy_bestsum(&I,&x);
  printf("\tGreedy Bestsum: %d\n", x.f);
  fprintf(f, "Greedy Bestsum,%d\n", x.f);
  clean_solution(&x);
  greedy_bestpair(&I,&x);
  printf("\tGreedy Bestpair: %d\n", x.f);
  fprintf(f, "Greedy Bestpair,%d\n", x.f);
  clean_solution(&x);
  greedy_tryall(&I,&x);
  printf("\tGreedy Tryall: %d\n", x.f);
  fprintf(f, "Greedy Tryall,%d\n", x.f);

  float uniform_grasp_score = 0;
  for(int i=0; i<seeds; i++)
  {
    srand(i);
    clean_solution(&x);
    uniform_grasp(&I,&x);
    uniform_grasp_score+= (float)x.f/(float)seeds;
  }
  printf("\t[Average] GRASP uniform: %f\n", uniform_grasp_score);
  fprintf(f, "[Average] GRASP uniform,%f\n", uniform_grasp_score);

  float linear_HBSS_grasp_score = 0;
  for(int i=0; i<seeds; i++)
  {
    srand(i);
    clean_solution(&x);
    linear_HBSS_grasp(&I,&x);
    linear_HBSS_grasp_score+= (float)x.f/(float)seeds;
  }
  printf("\t[Average] GRASP linear HBSS: %f\n", linear_HBSS_grasp_score);
  fprintf(f, "[Average] GRASP linear HBSS,%f\n", linear_HBSS_grasp_score);

  float exponential_HBSS_grasp_score = 0;
  for(int i=0; i<seeds; i++)
  {
    srand(i);
    clean_solution(&x);
    exponential_HBSS_grasp(&I,&x);
    exponential_HBSS_grasp_score+= (float)x.f/(float)seeds;
  }
  printf("\t[Average] GRASP exponential HBSS: %f\n", exponential_HBSS_grasp_score);
  fprintf(f, "[Average] GRASP exponential HBSS,%f\n", exponential_HBSS_grasp_score);

  float linear_RCL_grasp_score = 0;
  for(int i=0; i<seeds; i++)
  {
    srand(i);
    clean_solution(&x);
    linear_RCL_grasp(&I,&x, cardinality);
    linear_RCL_grasp_score+= (float)x.f/(float)seeds;
  }
  printf("\t[Average] GRASP linear RCL (cardinality %d): %f\n", cardinality, linear_RCL_grasp_score);
  fprintf(f, "[Average] GRASP linear RCL (cardinality %d),%f\n", cardinality, linear_RCL_grasp_score);

  float exponential_RCL_grasp_score = 0;
  for(int i=0; i<seeds; i++)
  {
    srand(i);
    clean_solution(&x);
    exponential_RCL_grasp(&I,&x, cardinality);
    exponential_RCL_grasp_score+= (float)x.f/(float)seeds;
  }
  printf("\t[Average] GRASP exponential RCL (cardinality %d): %f\n", cardinality, exponential_RCL_grasp_score);
  fprintf(f, "[Average] GRASP exponential RCL (cardinality %d),%f\n", cardinality, exponential_RCL_grasp_score);*/

  float ant_score = 0;
  for(int i=0; i<seeds; i++)
  {
    srand(i);
    clean_solution(&x);
    ant_system(&I,&x, 200, oblivion, memory_mu, data_mu);
    ant_score+= (float)x.f/(float)seeds;
  }
  printf("\t[Average] Ant system: %f\n", ant_score);
  fprintf(f, "[Average] Ant system,%f\n", ant_score);

  fine = clock();
  tempo = (double) (fine - inizio) / CLOCKS_PER_SEC;

  printf("Required time: %10.6lf ms\n",tempo*1000);

  printf("\n");
  fclose(f);

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
