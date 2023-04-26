#include <stdio.h>
#include <math.h>
#include "task_definitions.h"
#include "dbf.h"

typedef struct {
    double P; // Period
    double B; // Budget
} capacity;



double sbf_t(capacity cap, time_instance t) {
    double x_t = (floor((t + 1) / q) - 1) * q - (cap.P - cap.B);
    double y_t = x_t - floor(x_t / cap.P) * cap.P - (cap.P - cap.B);
    y_t = (y_t > 0) ? y_t : 0;

    return (x_t < 0) ? 0 : (floor(x_t / cap.P) * cap.B + y_t);
}



double max_T_D(struct taskset tasks) {
    double max_diff = tasks.tasks[0].T - tasks.tasks[0].D;

    for (int task_idx = 1; task_idx < tasks.task_count; ++task_idx) {
        double current_diff = tasks.tasks[task_idx].T - tasks.tasks[task_idx].D;
        if (current_diff > max_diff) {
            max_diff = current_diff;
        }
    }

    return max_diff;
}

double max_D(struct taskset tasks) {
    double max_deadline = tasks.tasks[0].D; // Initialize max_deadline to the first task's D value

    for (int task_idx = 1; task_idx < tasks.task_count; ++task_idx) {
        double current_deadline = tasks.tasks[task_idx].D;
        if (current_deadline > max_deadline) {
            max_deadline = current_deadline;
        }
    }

    return max_deadline;
}



int main() {
    const int num_tasksets = 2; // Number of tasksets in the array
    struct taskset tasksets[num_tasksets];

    printf("\r\n ================ Testing task generation ================ \r\n");

    // Initialize tasksets
    for (int ts_idx = 0; ts_idx < num_tasksets; ++ts_idx) {
        tasksets[ts_idx].task_count = TASKSET_SIZE;

        for (int task_idx = 0; task_idx < tasksets[ts_idx].task_count; ++task_idx) {
            tasksets[ts_idx].tasks[task_idx].T = 8 * (task_idx + 1);
            tasksets[ts_idx].tasks[task_idx].C = 1 * (task_idx + 1);
            tasksets[ts_idx].tasks[task_idx].D = 8 * (task_idx - task_idx);
            tasksets[ts_idx].tasks[task_idx].u = tasksets[ts_idx].tasks[task_idx].C / tasksets[ts_idx].tasks[task_idx].T;
            printf("[Taskset %d, Task %d] T=%f; C=%f; D=%f, u=%f\n", ts_idx, task_idx, tasksets[ts_idx].tasks[task_idx].T, tasksets[ts_idx].tasks[task_idx].C, tasksets[ts_idx].tasks[task_idx].D, tasksets[ts_idx].tasks[task_idx].u);
        }
    }

    // Test the max_T_D and max_D functions
    printf("\r\n ================ Testing max_T_D and max_D functions ================ \r\n");
    for (int ts_idx = 0; ts_idx < num_tasksets; ++ts_idx) {
        double max_t_d = max_T_D(tasksets[ts_idx]);
        printf("[Taskset %d] The maximum value of T - D is: %f\n", ts_idx, max_t_d);

        double max_d = max_D(tasksets[ts_idx]);
        printf("[Taskset %d] The maximum value of D is: %f\n", ts_idx, max_d);
    }

    // Test the dbf_core function for a specific time instance
    printf("\r\n ================ Testing dbf_core function ================ \r\n");
    for (int ts_idx = 0; ts_idx < num_tasksets; ++ts_idx) {
        printf("Taskset %d:\r\n", ts_idx);
        for (int t = 0; t < 10; t++) {
            double d = dbf_core(tasksets[ts_idx], t);
            printf("At time instance %d, dbf = %f. \r\n", t, d);
        }
    }

    capacity cap;
    cap.P = 30; // Set the period value
    cap.B = 20;  // Set the budget value

    for (double t = 0; t < 30; t ++) {
      double sbf_result = sbf_t(cap, t);
      printf("SBF result: %f\n", sbf_result);
    }


    return 0;
}





