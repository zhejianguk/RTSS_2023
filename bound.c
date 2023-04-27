#include "bound.h"
#include "definitions.h"
#include <stdio.h>
#include <math.h>

// dbf function
double dbf(task *h, time_instance t) {
    double dbf_t;
    dbf_t = ((floor(t - h->D) / h->T) + 1) * h->C;
    return (dbf_t > 0) ? dbf_t : 0;
}

// dbf_core function
double dbf_core(taskset core_tasks, time_instance t) {
  double dbf_core_t = 0;

  for (int task_idx = 0; task_idx < core_tasks.task_count; task_idx++) {
      dbf_core_t = dbf_core_t + dbf(&core_tasks.tasks[task_idx], t);
  }
  return dbf_core_t;
}


double sbf_t(capacity cap, time_instance t) {
    double x_t = (floor((t + 1) / q) - 1) * q - (cap.P - cap.B);
    double y_t = x_t - (floor(x_t / cap.P) * cap.P) - (cap.P - cap.B);
    y_t = (y_t > 0) ? y_t : 0;

    return (x_t < 0) ? 0 : (floor(x_t / cap.P) * cap.B + y_t);
}

void taskset_utilization(taskset *ts) {
    double total_utilization = 0;

    for (int task_idx = 0; task_idx < ts->task_count; ++task_idx) {
        ts->tasks[task_idx].u = ts->tasks[task_idx].C / ts->tasks[task_idx].T; // Calculate and store the task's utilization in the u field
        total_utilization += ts->tasks[task_idx].u;
    }

    ts->U = total_utilization; // Store the total utilization in the taskset structure
}
