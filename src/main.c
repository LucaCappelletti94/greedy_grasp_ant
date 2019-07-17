#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <getopt.h>

#include "greedy.h"
#include "grasp.h"
#include "ant.h"
#include "log.h"

#define REGISTER(METHOD,N,...) \
  if (METHOD ## _flag) \
  { \
    for(int i=0; i<N; i++) \
    { \
        METHOD(__VA_ARGS__);\
        scores[i] = px.f;\
        clean_solution(&px);\
    } \
    log_result(fp, verbose, #METHOD, scores, N);\
    }

int main (int argc, char *argv[])
{
  char data_file[NAME_LENGTH];
  data_t pI;
  solution_t px;
  time_t start = clock();
  FILE *fp = NULL;
  char ch;
  int * scores;
  int executions=10, iterations=200, rcl_max=10, mu_memory=5, mu_data=5, verbose = 0;
  double oblivion=0.1;
  int greedy_flag, greedy_bestsum_flag, greedy_bestpair_flag, greedy_tryall_flag, uniform_grasp_flag,
       linear_HBSS_grasp_flag, exponential_HBSS_grasp_flag, uniform_RCL_grasp_flag, linear_RCL_grasp_flag,
       exponential_RCL_grasp_flag, ant_system_flag, all_flag;
  greedy_flag = greedy_bestsum_flag = greedy_bestpair_flag = greedy_tryall_flag = uniform_grasp_flag =
  linear_HBSS_grasp_flag = exponential_HBSS_grasp_flag = uniform_RCL_grasp_flag = linear_RCL_grasp_flag =
  exponential_RCL_grasp_flag = ant_system_flag = all_flag = 0;


  struct option long_options[] = {
      {"data", required_argument, NULL, 'd'},
      {"log", required_argument, NULL, 'l'},
      {"executions", required_argument, &executions, 0},
      {"iterations", required_argument, &iterations, 0},
      {"rcl_max", required_argument, &rcl_max, 0},
      {"mu_memory", required_argument, &mu_memory, 0},
      {"mu_data", required_argument, &mu_data, 0},
      {"oblivion", required_argument, NULL, 'o'},
      {"verbose", no_argument, &verbose, 1},
      {"greedy", no_argument, &greedy_flag, 1},
      {"greedy_bestsum", no_argument, &greedy_bestsum_flag, 1},
      {"greedy_bestpair", no_argument, &greedy_bestpair_flag, 1},
      {"greedy_tryall", no_argument, &greedy_tryall_flag, 1},
      {"uniform_grasp", no_argument, &uniform_grasp_flag, 1},
      {"linear_HBSS_grasp", no_argument, &linear_HBSS_grasp_flag, 1},
      {"exponential_HBSS_grasp", no_argument, &exponential_HBSS_grasp_flag, 1},
      {"uniform_RCL_grasp", no_argument, &uniform_RCL_grasp_flag, 1},
      {"linear_RCL_grasp", no_argument, &linear_RCL_grasp_flag, 1},
      {"exponential_RCL_grasp", no_argument, &exponential_RCL_grasp_flag, 1},
      {"ant_system", no_argument, &ant_system_flag, 1},
      {"all", no_argument, &all_flag, 1},
      {NULL, 0, NULL, 0}
  };

  // loop over all of the options
  while ((ch = getopt_long(argc, argv, "d:l:o:", long_options, NULL)) != -1)
  {
    // check to see if a single character or long option came through
    switch (ch)
    {
      case 'd':
        strcpy(data_file, optarg);
        break;
      case 'l':
        fp = fopen(optarg, "w+");
        log_header(fp);
        break;
      case 'o':
        sscanf(optarg, "%lf", &oblivion);
        break;
    }
  }

  if (all_flag)
  {
    greedy_flag = greedy_bestsum_flag = greedy_bestpair_flag = greedy_tryall_flag = uniform_grasp_flag =
    linear_HBSS_grasp_flag = exponential_HBSS_grasp_flag = uniform_RCL_grasp_flag = linear_RCL_grasp_flag =
    exponential_RCL_grasp_flag = ant_system_flag = 1;
  }

  if (verbose) {
    printf("Data file: %s\n", data_file);
    printf("Score average over %d executions.\n", executions);
  }

  load_data(data_file,&pI);
  create_solution(pI.n,&px);
  scores = calloc(executions, sizeof(int));

  REGISTER(greedy, 1, &pI, &px)
  REGISTER(greedy_bestsum, 1, &pI, &px)
  REGISTER(greedy_bestpair, 1, &pI, &px)
  REGISTER(greedy_tryall, 1, &pI, &px)
  REGISTER(uniform_grasp, executions, &pI, &px, iterations)
  REGISTER(linear_HBSS_grasp, executions, &pI, &px, iterations)
  REGISTER(exponential_HBSS_grasp, executions, &pI, &px, iterations)
  REGISTER(uniform_RCL_grasp, executions, &pI, &px, iterations, rcl_max)
  REGISTER(linear_RCL_grasp, executions, &pI, &px, iterations, rcl_max)
  REGISTER(exponential_RCL_grasp, executions, &pI, &px, iterations, rcl_max)
  REGISTER(ant_system, executions,  &pI, &px, iterations, oblivion, mu_memory, mu_data)

  if (verbose)
    printf("Required time: %10.6lf ms\n", ((double) (clock() - start) / CLOCKS_PER_SEC) * 1000);

  destroy_solution(&px);
  destroy_data(&pI);

  return EXIT_SUCCESS;
}