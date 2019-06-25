#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "greedy.h"
#include "grasp.h"


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

  int cardinality = 10;
  int seeds = 500;

  inizio = clock();
  create_solution(I.n,&x);
  greedy(&I,&x);
  int greedy_score = x.f;
  create_solution(I.n,&x);
  greedy_bestsum(&I,&x);
  int greedy_bestsum_score = x.f;
  create_solution(I.n,&x);
  greedy_bestpair(&I,&x);
  int greedy_bestpair_score = x.f;
  create_solution(I.n,&x);
  greedy_tryall(&I,&x);
  int greedy_tryall_score = x.f;

  float uniform_grasp_score = 0;
  for(int i=0; i<seeds; i++)
  {
    srand(i);
    create_solution(I.n,&x);
    uniform_grasp(&I,&x);
    uniform_grasp_score+= (float)x.f/(float)seeds;
  }

  float linear_HBSS_grasp_score = 0;
  for(int i=0; i<seeds; i++)
  {
    srand(i);
    create_solution(I.n,&x);
    linear_HBSS_grasp(&I,&x);
    linear_HBSS_grasp_score+= (float)x.f/(float)seeds;
  }

  float exponential_HBSS_grasp_score = 0;
  for(int i=0; i<seeds; i++)
  {
    srand(i);
    create_solution(I.n,&x);
    exponential_HBSS_grasp(&I,&x);
    exponential_HBSS_grasp_score+= (float)x.f/(float)seeds;
  }

  float linear_RCL_grasp_score = 0;
  for(int i=0; i<seeds; i++)
  {
    srand(i);
    create_solution(I.n,&x);
    linear_RCL_grasp(&I,&x, cardinality);
    linear_RCL_grasp_score+= (float)x.f/(float)seeds;
  }

  float exponential_RCL_grasp_score = 0;
  for(int i=0; i<seeds; i++)
  {
    srand(i);
    create_solution(I.n,&x);
    exponential_RCL_grasp(&I,&x, cardinality);
    exponential_RCL_grasp_score+= (float)x.f/(float)seeds;
  }

  fine = clock();
  tempo = (double) (fine - inizio) / CLOCKS_PER_SEC;

  printf("Data file: %s\n",data_file);
  printf("Required time: %10.6lf ms\n",tempo*1000);
  printf("Scores:\n");
  printf("\tGreedy: %d\n", greedy_score);
  printf("\tGreedy Bestsum: %d\n", greedy_bestsum_score);
  printf("\tGreedy Bestpair: %d\n", greedy_bestpair_score);
  printf("\tGreedy Tryall: %d\n", greedy_tryall_score);
  printf("\t[Average] GRASP uniform: %f\n", uniform_grasp_score);
  printf("\t[Average] GRASP linear HBSS: %f\n", linear_HBSS_grasp_score);
  printf("\t[Average] GRASP exponential HBSS: %f\n", exponential_HBSS_grasp_score);
  printf("\t[Average] GRASP linear RCL (cardinality %d): %f\n", cardinality, linear_RCL_grasp_score);
  printf("\t[Average] GRASP exponential RCL (cardinality %d): %f\n", cardinality, exponential_RCL_grasp_score);
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
