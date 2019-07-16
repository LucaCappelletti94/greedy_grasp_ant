# greedy_grasp_ant
[![Build Status](https://travis-ci.org/LucaCappelletti94/greedy_grasp_ant.svg?branch=master)](https://travis-ci.org/LucaCappelletti94/greedy_grasp_ant) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/3cdaec8507ce46cd961b2885d2ef9d06)](https://www.codacy.com/app/LucaCappelletti94/greedy_grasp_ant?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=LucaCappelletti94/greedy_grasp_ant&amp;utm_campaign=Badge_Grade)

Small C project to highlight the similarities of Greedy, GRASP and Ant system algorithms.

![Normalized min max scores](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/scores/scores.png?raw=true)
To visualize the scores of the various datasets, scores have been min-max normalized for each dataset column.

## Building and running the program
To build the program just run the following:

```bash
mkdir my_test_dir
cd my_test_dir
cmake ..
make
```
Then to run the software just build just execute the following, where `{my_dataset}` is a valid dataset under `/data`, such as `01matrizn100m10.dat`:
```bash
./greedy_grasp_ant data/{my_dataset}
```

The output will be something of the following fashion:

```plain
Data file: data/14matrizn400m80.dat
Total algorithms: 10.
Score average over 10 executions.
	Greedy: 16653
	Greedy bestsum: 16679
	Greedy bestpair: 16653
	Greedy tryall: 16824
	Uniform GRASP: 14273
	Linear HBSS GRASP: 14937
	Exponential HBSS GRASP: 16624
	Linear RCL GRASP: 16512
	Exponential RCL GRASP: 16624
	Ant System: 16588
Required time: 95895.153000 ms
```

## Greedy
The [greedy algorithm implementation](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/src/greedy.c) is a simple loop in which, at every iteration, the best point is selected:

```c
void greedy (data_t *pI, solution_t *px)
{
  while (px->card_x < pI->k)
    move_point_in(best_additional_point(px,pI),px,pI);
}
```

## GRASP
The [GRASP algorithm implementation](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/src/greedy.c) contains multiple implementations for the various distributions:

-   [Uniform](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/53df14aa325d75fd5270075b2880834c8a6c5901/src/distributions.c#L16-L23): the algorithm will be a random search.
-   [HBSS](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/53df14aa325d75fd5270075b2880834c8a6c5901/src/distributions.c#L35-L43): weight the solutions probabilities on their quality, following either linear or exponential distribution.
-   [RCL](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/53df14aa325d75fd5270075b2880834c8a6c5901/src/distributions.c#L56-L64): like HBSS, but with a cardinality limit. The solutions above the given cardinality get probability zero.

```c
void grasp(data_t *pI, solution_t *px, size_t max, double* (*get_distribution)(int**, size_t, size_t))
{
  while (px->card_x < pI->k)
    move_point_in(random_additional_point(px, pI, max, get_distribution),px,pI);
}
```

The available distributions can be seen [here](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/src/distributions.c).

## Ant System
Finally, the [Ant System Algorithm implementation](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/src/ant.c) goes a step further than the grasp, introducing a memory, called trace.

```c
void ant_system(data_t *pI, solution_t *px, int iterations, double oblivion, double mu_memory, double mu_data)
{
  double* trace = init_trace(pI->n);
  for(int i=1; i<=iterations; i++){
    while (px->card_x < pI->k)
      move_point_in(ant_additional_point(px, pI, trace, mu_memory, mu_data), px, pI);
    update_trace(px, oblivion, trace, pI->n);
    if(i!=iterations)
      clean_solution(px);
  }
  free(trace);
}
```

Using a [Gaussian process](https://github.com/LucaCappelletti94/gaussian_process) ([script implementation here](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/scripts/bayes.py)) for tuning the `oblivion`, `mu_memory` and `mu_data` parameters for a `1000` iterations a peculiar result was obtained: the best parameters where those, in the context of the dataset `14matrizn400m80.dat`, which make the ant system behave more closely to a greedy algorithm.

```c
void parametrized_ant_system(data_t *d, solution_t *x)
{
  ant_system(d, x, 200, 0.2, 2, 78);
}
```

## Repository structure
The repository is structured as follows:

-   [`/data`](https://github.com/LucaCappelletti94/greedy_grasp_ant/tree/master/data): contains the project data, as in the weighted graphs on which the varius algorithms can be tested.
-   [`/scores`](https://github.com/LucaCappelletti94/greedy_grasp_ant/tree/master/scores): containes the scores obtained by running every algorithm on every available dataset, their summary and heatmap image.
-   [`/scripts`](https://github.com/LucaCappelletti94/greedy_grasp_ant/tree/master/scripts)
	-   [`bayes.py`](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/scripts/bayes.py): python script to execute bayesian optimization of the hyper parameters for the ant system algorithm.
	-   [`multiproc.py`](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/scripts/multiproc.py): python script to run the program on every available dataset in a parallel fashion.
	-   [`.gaussian_process`](https://github.com/LucaCappelletti94/greedy_grasp_ant/tree/master/scripts/.gaussian_process): cache folder for the gaussian process, storing the datapoints and their respective scores already explored by the bayesian optimization.
-   [`/src`](https://github.com/LucaCappelletti94/greedy_grasp_ant/tree/master/src): the project itself, containing the source code. Detailed explanation of the project structure is [available down below](https://github.com/LucaCappelletti94/greedy_grasp_ant#project-structure).
-   [`/.gitignore`](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/.gitignore): git settings file for avoiding to upload unwanted files.
-   [`/.travis.yml`](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/.travis.yml): travis settings file for automated build testing and evaluation.
-   [`/CMakeLists.txt`](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/CMakeLists.txt): cmake settings file for meta-building the project and creating a make file for actually building it. [Instruction for building the program are available here](https://github.com/LucaCappelletti94/greedy_grasp_ant#building-and-running-the-program).
-   [`/README.md`](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/README.md): markdown file containing a short project description.

## Project structure
The [project source code](https://github.com/LucaCappelletti94/greedy_grasp_ant) is structured as follows:

-   [`/src/alloc.c`](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/src/alloc.c): functions for allocating various types of multi-dimensions vectors.
-   [`/src/data.c`](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/src/data.c): functions for loading, visualizing and destroying the dataset.
-   [`/src/utils.c`](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/src/utils.c): utilities.
-   [`/src/distances.c`](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/src/distances.c): functions for alocating the distances vectors, calculating them given a solution and the available points and destroying them.
-   [`/src/solution.c`](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/src/solution.c): functions for allocating, updating and destroying solutions.
-   [`/src/distributions.c`](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/src/distributions.c): functions for allocating stocastic vectors and calculating distributions given distances scores.
-   [`/src/greedy.c`](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/src/greedy.c): implementation of Greedy.
-   [`/src/grasp.c`](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/src/grasp.c): implementation of GRASP.
-   [`/src/ant.c`](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/src/ant.c): implementation of ant system.
-   [`/src/main.c`](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/src/main.c): main of the program, which executes every available algorithm on the given data.
