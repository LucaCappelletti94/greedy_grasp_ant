//
// Created by Luca Cappelletti on 2019-06-25.
//

#include "distributions.h"


int choice(const float* p, size_t n)
{
  float rnd = (float)rand() / (float)RAND_MAX;
  int i;
  for(i=0; i<n && rnd > p[i]; rnd-=p[i], i++);
  return i;
}

float* uniform(int** distances, size_t n, size_t max)
{
  float* distribution = (float*) malloc(n* sizeof(float));
  for(int i=0; i<n; i++){
    distribution[i] = 1.0/(float)n;
  }
  return distribution;
}

float linear_schema(int i, int n)
{
  return (float)(n-i)/((float)(n*(n+1))/2.0);
}

float exponential_schema(int i, int n)
{
  return exp(n-i-1) / ((1-exp(n))/(1-exp(1)));
}

float* HBSS(int** distances, int n, float (*schema)(int, int))
{
  sort_distances(distances, n);
  float* distribution = (float*) malloc(n* sizeof(float));
  for(int i=0; i<n; i++){
    distribution[i] = schema(i, n);
  }
  return distribution;
}

float* linear_HBSS(int** distances, size_t n, size_t max)
{
  return  HBSS(distances, n, linear_schema);
}

float* exponential_HBSS(int** distances, size_t n, size_t max)
{
  return  HBSS(distances, n, exponential_schema);
}

// Implementation of RCL with cardinality limit
float* RCL(int** distances, int n, float (*schema)(int, int), int max_n)
{
  float* distribution = HBSS(distances, n, schema);
  float delta = 0;
  for(int i=max_n; i<n; delta+=distribution[i], distribution[i] = 0, i++);
  for(int i=0; i<=max_n; i++)
    distribution[i]/=(1-delta);
  return distribution;
}

float* linear_RCL(int** distances, size_t n, size_t max)
{
  return  RCL(distances, n, linear_schema, max);
}

float* exponential_RCL(int** distances, size_t n, size_t max)
{
  return  RCL(distances, n, exponential_schema, max);
}