#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "definitions.h"


void uunifast(int n, double U, taskset *ts) {
    double sum_u = U;
    for (int i = 0; i < n - 1; ++i) {
        double p = (double)rand() / (double)RAND_MAX;
        ts->tasks[i].u = sum_u * (1 - pow(p, 1.0 / (n - i)));
        sum_u -= ts->tasks[i].u;
    }
    ts->tasks[n - 1].u = sum_u;

    for (int i = 0; i < n; ++i) {
        ts->tasks[i].T = rand() % 1000 + 1;
        ts->tasks[i].C = ts->tasks[i].u * ts->tasks[i].T;
        ts->tasks[i].D = ts->tasks[i].T; // Assuming deadline equals period
    }

    ts->task_count = n;
    ts->U = U;
}

void uunifast_per_core(int n, double U, taskset ts[NUM_CORES]) {
    double sum_u = U;
    int total_tasks = n * NUM_CORES;

    double* all_task_utilizations = (double*)malloc(total_tasks * sizeof(double));

    for (int i = 0; i < total_tasks - 1; ++i) {
        double p = (double)rand() / (double)RAND_MAX;
        all_task_utilizations[i] = sum_u * (1 - pow(p, 1.0 / (total_tasks - i)));
        sum_u -= all_task_utilizations[i];
    }
    all_task_utilizations[total_tasks - 1] = sum_u;

    int task_index = 0;
    for (int core = 0; core < NUM_CORES; ++core) {
        double core_sum_u = 0;

        for (int i = 0; i < n; ++i) {
            ts[core].tasks[i].u = all_task_utilizations[task_index];
            core_sum_u += all_task_utilizations[task_index];
            task_index++;

            ts[core].tasks[i].T = rand() % 1000 + 1;
            ts[core].tasks[i].C = fmax(round(ts[core].tasks[i].u * ts[core].tasks[i].T / q) * q, q);
            ts[core].tasks[i].D = ts[core].tasks[i].T; // Assuming deadline equals period
        }

        ts[core].task_count = n;
        ts[core].U = core_sum_u;
    }

    free(all_task_utilizations);
}

/*
int main() {
    srand(time(NULL));

    int n = TASKSET_SIZE;
    double U = 0.5;
    
    taskset ts_all;

    uunifast(n, U, &ts_all);

    printf("Task set with total utilization %.2f:\n", ts_all.U);
    U = 0;
    for (int i = 0; i < ts_all.task_count; ++i) {
        printf("Task %d: Utilization = %.4f, Computation Time = %.2f, Period = %.2f, Deadline = %.2f\n\r",
               i + 1, ts_all.tasks[i].u, ts_all.tasks[i].C, ts_all.tasks[i].T, ts_all.tasks[i].D);
               U = U + ts_all.tasks[i].u;
    }
    printf ("The total utilization is %f \r\n", U);

    taskset ts[NUM_CORES];
    uunifast_per_core(n, U, ts);
    U = 0;
    for (int core = 0; core < NUM_CORES; ++core) {
        double total_utilization = 0;
        for (int i = 0; i < ts[core].task_count; ++i) {
            printf("Task %d: Utilization = %.4f, Computation Time = %.4f, Period = %.4f, Deadline = %.4f\n",
                   i + 1, ts[core].tasks[i].u, ts[core].tasks[i].C, ts[core].tasks[i].T, ts[core].tasks[i].D);
            total_utilization += ts[core].tasks[i].u;
        }
        U = U + total_utilization;
        printf("The total utilization for Core %d is %f\n", core, total_utilization);
    }
    printf("The total utilization for system is %f\n", U);

    return 0;
}
*/