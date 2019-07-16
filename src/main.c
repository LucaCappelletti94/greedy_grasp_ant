#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "greedy.h"
#include "grasp.h"
#include "ant.h"


int multiple_executions(int executions, solution_t *x, data_t *d, void (*algorithm)(data_t*, solution_t*))
{
  int score = 0;
  for(int seed=0; seed<executions; seed++)
  {
    srand(seed);
    clean_solution(x);
    algorithm(d,x);
    score+=x->f;
  }
  return (int)round((double)score/(double)executions);
}

void print_score(char *name, int score)
{
  printf("\t%s: %d\n", name, score);
}

void run(int executions, solution_t *x, data_t *d, char *name, void (*algorithm)(data_t*, solution_t*))
{
  print_score(name, multiple_executions(executions, x, d, algorithm));
}

int main (int argc, char *argv[])
{
  char data_file[NAME_LENGTH];
  data_t I;
  solution_t x;
  time_t start = clock();
  int executions = 10;
  int total_algorithms = 11;

  strcpy(data_file,argv[1]);
  void (*algorithms[])(data_t*, solution_t*) = {
          greedy, greedy_bestsum, greedy_bestpair, greedy_tryall,
          parametrized_uniform_grasp, parametrized_linear_HBSS_grasp, parametrized_exponential_HBSS_grasp,
          parametrized_uniform_RCL_grasp, parametrized_linear_RCL_grasp, parametrized_exponential_RCL_grasp,
          parametrized_ant_system
  };
  char *names[] = {
          "Greedy", "Greedy bestsum", "Greedy bestpair", "Greedy tryall",
          "Uniform GRASP", "Linear HBSS GRASP", "Exponential HBSS GRASP",
          "Uniform RCL GRASP", "Linear RCL GRASP", "Exponential RCL GRASP",
          "Ant System"
  };

  printf("Data file: %s\n",data_file);
  printf("Total algorithms: %d.\n", total_algorithms);
  printf("Score average over %d executions.\n", executions);

  load_data(data_file,&I);
  create_solution(I.n,&x);
  for (int i=0; i<total_algorithms; i++)
    run(executions, &x, &I, names[i], algorithms[i]);

  printf("Required time: %10.6lf ms\n",((double) (clock() - start) / CLOCKS_PER_SEC)*1000);

  destroy_solution(&x);
  destroy_data(&I);

  return EXIT_SUCCESS;
}