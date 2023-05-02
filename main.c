#include <stdio.h>
#include "definitions.h"
#include "bound.h"

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
  
  schedulability_test(&ts, &cap);
  printf("U = %f \r\n", ts.U);
  printf("w = %f \r\n", cap.w);

  return 1;
}





