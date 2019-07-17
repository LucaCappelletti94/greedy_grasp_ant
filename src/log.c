//
// Created by Luca Cappelletti on 2019-07-17.
//

#include "log.h"

void print_score(char *name, int mean, int std, int var, int min, int max)
{
  printf("%s: ", name);

  if (var!=0){
    printf("\n");
    printf("\tmean: %d\n", mean);
    printf("\tstd: %d\n", std);
    printf("\tvar: %d\n", var);
    printf("\tmin: %d\n", min);
    printf("\tmax: %d\n", max);
  } else {
    printf("%d\n", mean);
  }
}

void log_header(FILE *fp)
{
  fprintf(fp, "name,mean,std,var,min,max\n");
}

void log_score(FILE *fp, char *name, int mean, int std, int var, int min, int max)
{
  fprintf(fp, "%s,%d,%d,%d,%d,%d\n", name, mean, std, var, min, max);
}

void log_result(FILE *fp, int verbose, char *name, int* scores, int executions)
{
  int mean = int_mean(scores, executions);
  int var = int_var(scores, executions);
  int std = int_std(scores, executions);
  int min = int_min(scores, executions);
  int max = int_max(scores, executions);

  if (verbose)
    print_score(name, mean, std, var, min, max);

  if (fp)
    log_score(fp, name, mean, std, var, min, max);
}