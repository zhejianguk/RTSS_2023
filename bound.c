#include "bound.h"
#include "definitions.h"
#include <stdio.h>
#include <math.h>

double max_T_D(taskset tasks) {
    double max_diff = tasks.tasks[0].T - tasks.tasks[0].D;

    for (int task_idx = 1; task_idx < tasks.task_count; ++task_idx) {
        double current_diff = tasks.tasks[task_idx].T - tasks.tasks[task_idx].D;
        if (current_diff > max_diff) {
            max_diff = current_diff;
        }
    }

    return max_diff;
}

double min_D(taskset tasks) {
    double min_deadline = tasks.tasks[0].D;

    for (int task_idx = 1; task_idx < tasks.task_count; ++task_idx) {
        double current_deadline = tasks.tasks[task_idx].D;
        if (current_deadline < min_deadline) {
            min_deadline = current_deadline;
        }
    }

    return min_deadline;
}


// dbf function
double dbf(task *h, time_instance t) {
    double dbf_t;
    dbf_t = (floor((t - h->D) / h->T) + 1) * h->C;
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

int schedulability_test(taskset *ts, capacity *cap) {
  cap->w = cap->B/cap->P;
  printf("%f====\r\n", cap->w);
  taskset_utilization(ts);

  double w = cap->w;
  double U = ts->U;
  if (U >= w){
    printf("================ Unschedule ================ \r\n");
    printf("U>=w, U = %f, w= %f \r\n", U, w);
    return -1;
  }

  double eta = max_T_D(*ts);
  double Z = (eta*U + 2*(q-1+cap->P-cap->B)*w)/(w-U);
  double t_start = min_D(*ts);

  for (double t = t_start; t < Z; t++){
    double d = dbf_core(*ts, t);
    double s = sbf_t(*cap, t);
    if (d > s) {
      printf("================ Unschedule ================ \r\n");
      printf("d > s at t %f, d = %f, s = %f \r\n", t, d, s);
      return -1;
    }
  }

  printf ("*** Paseed *** \r\n");


  return 0;
}