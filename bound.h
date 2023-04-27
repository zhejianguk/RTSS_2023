#ifndef BOUND_H
#define BOUND_H

#include "definitions.h"

double dbf_core(taskset core_tasks, time_instance t);
double sbf_t(capacity cap, time_instance t);
void taskset_utilization(taskset *ts);

#endif // DBF_FUNCTIONS_H
