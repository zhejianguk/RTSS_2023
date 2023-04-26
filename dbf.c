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
double dbf_core(struct taskset core_tasks, time_instance t) {
  double dbf_core_t = 0;

  for (int task_idx = 0; task_idx < core_tasks.task_count; task_idx++) {
      dbf_core_t = dbf_core_t + dbf(&core_tasks.tasks[task_idx], t);
  }
  return dbf_core_t;
}
