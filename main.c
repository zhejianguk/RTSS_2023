#include <stdio.h>
#include "definitions.h"
#include "bound.h"
#include "min_budget.h"

int main() {
  taskset ts;
  capacity cap;

  cap.P = 80;
  cap.B = 48;

  ts.task_count = TASKSET_SIZE;
  for (int task_idx = 0; task_idx < ts.task_count; ++task_idx) {
      ts.tasks[task_idx].T = 80 * (task_idx + 1);
      ts.tasks[task_idx].C = 4 * (task_idx + 1);
      ts.tasks[task_idx].D = 80 * (task_idx + 1); // Implicated Deadline
  }
  
  int sch = schedulability_test(&ts, &cap);
  if (sch == 0){
    printf ("*** Paseed *** \r\n");
  }
  else {
    printf ("*** Failed *** \r\n");
  }

  // double min_budget_t = min_budget(&ts, cap.P);

  // printf ("*** The min_budget =  %f *** \r\n", min_budget_t);

  
  return 1;
}





