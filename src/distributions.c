//
// Created by Luca Cappelletti on 2019-06-25.
//

#include "distributions.h"


int choice(const double* p, size_t n)
{
  double rnd = (double)rand() / (double)RAND_MAX;
  int i;
  for(i=0; i<n-1 && rnd >= p[i]; rnd-=p[i], i++);
  return i;
}

double uniform_schema(int i, int n)
{
  return 1.0/(double)(n);
}

double linear_schema(int i, int n)
{
  return (double)(n-i)/((double)(n*(n+1))/2.0);
}

double exponential_schema(int i, int n)
{
  return exp(n-i-1) / ((1-exp(n))/(1-exp(1)));
}

double* HBSS(int** distances, int n, double (*schema)(int, int))
{
  sort_distances(distances, n);
  double* distribution = double_alloc(n);
  for(int i=0; i<n; i++){
    distribution[i] = schema(i, n);
  }
  return distribution;
}

// Implementation of RCL with cardinality limit
double* RCL(int** distances, int n, double (*schema)(int, int), int max_n)
{
  if (max_n > n) {
    max_n = n-1;
  }
  double* distribution = HBSS(distances, n, schema);
  double delta = 0;
  for(int i=max_n; i<n; delta+=distribution[i], distribution[i] = 0, i++);
  for(int i=0; i<max_n; i++)
    distribution[i]/=(1-delta);
  return distribution;
}

double* uniform_RCL(int** distances, size_t n, size_t max)
{
  return  RCL(distances, n, uniform_schema, max);
}

double* linear_RCL(int** distances, size_t n, size_t max)
{
  return  RCL(distances, n, linear_schema, max);
}

double* exponential_RCL(int** distances, size_t n, size_t max)
{
  return  RCL(distances, n, exponential_schema, max);
}

int random_index(int** distances, double* distribution, size_t n)
{
  int position = choice(distribution, n);
  int distance_index = distances[0][position];
  return distance_index;
}