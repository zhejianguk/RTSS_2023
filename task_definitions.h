#ifndef TASK_DEFINITIONS_H
#define TASK_DEFINITIONS_H

#define TASKSET_SIZE 40
#define q 2

typedef double time_instance;

// Structure for task
struct task {
    double T; // Period
    double C; // Computation time
    double D; // Deadline
    double u; // Utilisation
};

// Structure for taskset
struct taskset {
    struct task tasks[TASKSET_SIZE]; // Array of tasks
    int task_count; // Number of tasks in the taskset
};


#endif // TASK_DEFINITIONS_H
