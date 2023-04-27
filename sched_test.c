#include <stdio.h>
#include "definitions.h"
#include "bound.h"



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


int main() {
  taskset ts;

  // printf(" ================ Testing task generation ================ \r\n");
  capacity cap;
  cap.P = 30;
  cap.B = 20;

  ts.task_count = TASKSET_SIZE;
  for (int task_idx = 0; task_idx < ts.task_count; ++task_idx) {
      ts.tasks[task_idx].T = 20 * (task_idx + 1);
      ts.tasks[task_idx].C = 1 * (task_idx + 1);
      ts.tasks[task_idx].D = 100 * (task_idx + 1) - 10;
  }
  cap.w = cap.B/cap.P;
  taskset_utilization(&ts);

  double w = cap.w;
  double U = ts.U;
  if (U >= w){
    printf("================ Unschedule ================ \r\n");
    printf("U>=w, U = %f, w= %f \r\n", U, w);
    return 0;
  }

  double eta = max_T_D(ts);
  // printf("eta = %f \r\n",eta);
  double Z = (eta*U + 2*(q-1+cap.P-cap.B)*w)/(w-U);
  // printf("Z = %f \r\n",Z);
  double t_start = min_D(ts);
  // printf("t_start = %f \r\n",t_start);

  for (double t = t_start; t < Z; t++){
    double d = dbf_core(ts, t);
    double s = sbf_t(cap, t);
    if (d > s) {
      printf("================ Unschedule ================ \r\n");
      printf("d > s at t %f, d = %f, s = %f \r\n", t, d, s);
      return 0;
    }
  }

  printf ("*** Paseed *** \r\n");

  return 1;
}





