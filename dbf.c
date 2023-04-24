#include "dbf.h"
#include "task_definitions.h"
#include <stdio.h>

// dbf function
double dbf(struct task *h, time_instance t) {
    double dbf_t;
    dbf_t = (((t - h->D) / h->T) + 1) * h->C;
    return (dbf_t > 0) ? dbf_t : 0;
}

// dbf_core function
double dbf_core(taskset core_tasks, time_instance t) {
  double dbf_core_t;

  for (int task_idx = 0; task_idx < TASKSET_SIZE; task_idx++) {
      dbf_core_t = dbf_core_t + dbf(&core_tasks[task_idx], t);
  }
  return dbf_core_t;
}