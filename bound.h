#ifndef BOUND_H
#define BOUND_H

#include "definitions.h"

double min_D_C(taskset tasks);
double dbf_core(taskset core_tasks, time_instance t);
double sbf_t(capacity cap, time_instance t);
double total_bandwidth(capacity *cap);
void taskset_utilization(taskset *ts);
int schedulability_test(taskset *ts, capacity *cap);

#endif // DBF_FUNCTIONS_H
