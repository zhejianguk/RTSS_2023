#include <stdio.h>
#include <math.h>
#include "definitions.h"
#include "bound.h"
#include "min_budget.h"
#include "interface_select.h"

int main() {
  taskset ts[NUM_CORES];
  capacity cap[NUM_CORES];

  for (int core_idx = 0; core_idx < NUM_CORES; ++core_idx) {
    ts[core_idx].task_count = TASKSET_SIZE;

    for (int task_idx = 0; task_idx < ts[core_idx].task_count; ++task_idx) {
        ts[core_idx].tasks[task_idx].T = 80 * (task_idx + core_idx + 1);
        ts[core_idx].tasks[task_idx].C = 4 * (task_idx + core_idx + 1);
        ts[core_idx].tasks[task_idx].D = 80 * (task_idx + core_idx + 1); // Implicit Deadline
    }
    taskset_utilization(&ts[core_idx]);
  }


  int s = interface_select_all(ts, cap);
  if (s == 0){
    printf ("SUCCESS \r\n");
  } else {
    printf ("FAILURE \r\n");
  }

  for (int core_idx = 0; core_idx < NUM_CORES; ++core_idx){
    printf("Period = %f, Budget = %f \r\n", cap[core_idx].P, cap[core_idx].B);
  }


  return 0;
}





