#include <stdio.h>
#include "task_definitions.h"
#include "dbf.h"

typedef double time_instance;

int main() {
    taskset tasks;

    printf("\r\n ================ Testing task generation ================ \r\n");
    for (int task_idx = 0; task_idx < TASKSET_SIZE; ++task_idx) {
        tasks[task_idx].T = 8 * (task_idx + 1);
        tasks[task_idx].C = 1 * (task_idx + 1);
        tasks[task_idx].D = 8 * (task_idx * 2 + 1);
        tasks[task_idx].u = tasks[task_idx].C / tasks[task_idx].T;
        printf("[Task %d] T=%f; C=%f; D=%f, u=%f\n", task_idx, tasks[task_idx].T, tasks[task_idx].C, tasks[task_idx].D, tasks[task_idx].u);
    }

    // Test the dbf_core function for a specific time instance
    printf("\r\n ================ Testing dbf_core function ================ \r\n");
    for (int t = 0; t < 10; t++){
      double d = dbf_core(tasks, t);
      printf ("At time instance %x, dbf = %f. \r\n", t, d);
    }

    return 0;
}