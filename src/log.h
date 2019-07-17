//
// Created by Luca Cappelletti on 2019-07-17.
//

#ifndef GREEDY_GRASP_ANT_LOG_H
#define GREEDY_GRASP_ANT_LOG_H

#include <stdio.h>
#include "utils.h"

void log_header(FILE *fp);
void log_result(FILE *fp, int verbose, char *name, int* scores, int executions);

#endif //GREEDY_GRASP_ANT_LOG_H
