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

int main() {
    srand(time(NULL));

    int n = TASKSET_SIZE;
    double U = 0.5;
    taskset ts;

    uunifast(n, U, &ts);

    printf("Task set with total utilization %.2f:\n", ts.U);
    U = 0;
    for (int i = 0; i < ts.task_count; ++i) {
        printf("Task %d: Utilization = %.4f, Computation Time = %.2f, Period = %.2f, Deadline = %.2f\n\r",
               i + 1, ts.tasks[i].u, ts.tasks[i].C, ts.tasks[i].T, ts.tasks[i].D);
               U = U + ts.tasks[i].u;
    }
    printf ("The total utilization is %f \r\n", U);

    return 0;
}
