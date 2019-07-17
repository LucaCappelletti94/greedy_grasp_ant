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
./greedy_grasp_ant --data={my_dataset} --all --verbose
```

The output will be something of the following fashion:

```plain
Data file: ../data/01matrizn100m10.dat
Score average over 10 executions.
greedy: 306
greedy_bestsum: 322
greedy_bestpair: 306
greedy_tryall: 333
uniform_grasp: 
	mean: 211
	std: 14
	var: 220
	min: 191
	max: 237
linear_HBSS_grasp: 
	mean: 245
	std: 11
	var: 141
	min: 217
	max: 260
exponential_HBSS_grasp: 
	mean: 312
	std: 4
	var: 16
	min: 306
	max: 319
uniform_RCL_grasp: 
	mean: 287
	std: 5
	var: 28
	min: 278
	max: 295
linear_RCL_grasp: 
	mean: 289
	std: 8
	var: 72
	min: 277
	max: 308
exponential_RCL_grasp: 
	mean: 311
	std: 5
	var: 29
	min: 303
	max: 319
ant_system: 
	mean: 255
	std: 9
	var: 95
	min: 241
	max: 275
Required time: 102.841000 ms
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
The [GRASP algorithm implementation](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/src/grasp.c) contains multiple implementations for the various distributions:

-   [Uniform](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/53df14aa325d75fd5270075b2880834c8a6c5901/src/distributions.c#L16-L23): the algorithm will be a random search.
-   [HBSS](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/53df14aa325d75fd5270075b2880834c8a6c5901/src/distributions.c#L35-L43): weight the solutions probabilities on their quality, following either linear or exponential distribution.
-   [RCL](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/53df14aa325d75fd5270075b2880834c8a6c5901/src/distributions.c#L56-L64): like HBSS, but with a cardinality limit. The solutions above the given cardinality get probability zero.

```c
void grasp(data_t *pI, solution_t *px, int iterations, size_t max, double* (*get_distribution)(int**, size_t, size_t))
{
  solution_t best;
  create_solution(px->card_N, &best);
  for(int i=1; i<=iterations; i++) {
    // While the current solution cardinality is less than the maximum allowed
    // as specified in the input file.
    while (!is_solution_feasible(pI, px))
      move_point_in(random_additional_point(px, pI, max, get_distribution), px, pI);
    if (best.f < px->f) {
      copy_solution(px, &best);
      clean_solution(px);
    }
  }
  copy_solution(&best, px);
}
```

The available distributions can be seen [here](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/src/distributions.c).

## Ant System
Finally, the [Ant System Algorithm implementation](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/src/ant.c) goes a step further than the grasp, introducing a memory, called trace.

```c
void ant_system(data_t *pI, solution_t *px, int iterations, double oblivion, double mu_memory, double mu_data)
{
  double* trace = init_trace(pI->n);
  solution_t best;
  create_solution(px->card_N, &best);
  for(int i=1; i<=iterations; i++){
    // While the current solution cardinality is less than the maximum allowed
    // as specified in the input file.
    while (!is_solution_feasible(pI, px))
      move_point_in(ant_additional_point(px, pI, trace, mu_memory, mu_data), px, pI);
    if (best.f < px->f)
    {
      copy_solution(px, &best);
      clean_solution(px);
      update_trace(&best, oblivion, trace, pI->n);
    }
  }
  copy_solution(&best, px);
  free(trace);
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


## Available options
There are a number of available options.

### Required options
The only required options are the data file path and at least an implementation. The available implementations are listed below, and the data file path can be specified as follows:

```bash
--data={my_dataset} --{any_available_implementation}
```

or alternatively:

```bash
--data {my_dataset} --{any_available_implementation}
```

### Available implementations
To run one or more implementations, just pass the corresponding options. The available options are:

-   `--greedy`
-   `--greedy_bestsum`
-   `--greedy_bestpair`
-   `--greedy_tryall`
-   `--uniform_grasp`
-   `--linear_HBSS_grasp`
-   `--exponential_HBSS_grasp`
-   `--uniform_RCL_grasp`
-   `--linear_RCL_grasp`
-   `--exponential_RCL_grasp`
-   `--ant_system`

To run **every** available implementation pass only the option `--all`.

### Custom parameters
For every parameters used there is a default parameter but also the possibility to pass the value by option. Here's the available options for setting the parameters:

-   `--executions`: number of the test executions (integer).
-   `--iterations`: number of iterations for grasp and ant (integer).
-   `--rcl_max`: maximum number of elements to consider in RCL (integer).
-   `--mu_memory`: trace coefficient for ant (integer).
-   `--mu_data`: data coefficient for ant (integer).
-   `--oblivion`: trace oblivion coefficient for ant (double).
  
Every parameter is used like `data`, as follows:

```bash
--{parameter}={parameter_value}
```

or equivalently:

```bash
--{parameter} {parameter_value}
```

### Utilities related options
Two utilities are available:

#### Verbose    
When specified as `--verbose`, verbose prints output to stdout, otherwise it will remain muted.

#### Log
When specified as `--log={csv_log_file}`, the scripts results will be logged to `csv_log_file` in csv file format.

## Multiprocess bayesian tuning for ant-system hyper-parameters
Using a [Gaussian process](https://github.com/LucaCappelletti94/gaussian_process) ([script implementation here](https://github.com/LucaCappelletti94/greedy_grasp_ant/blob/master/scripts/bayes.py)) we can tune the `oblivion`, `mu_memory` and `mu_data` parameters for the ant-system as follows.

First we build the project:

```bash
mkdir gga
cd gga
cmake ..
make
cd ..
```

Then we install the required python packages:

```bash
python -m pip install -r requirements.txt
```

and finally we run the gaussian process:

```bash
python scripts/bayes.py
```

Other than printing the best parameters at the end, they will also be saved in the `best_parameters.json` file.

## Multiprocess implementations scores determination
After having built the project and installed the python requirements, as explained the gaussian process section, we can run the following:

```bash
python scripts/multiproc.py
```

The cumulative results will be stores in `scores/all_scores.csv` and the single files will be stored in `scores`.