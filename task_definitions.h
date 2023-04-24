#ifndef TASK_DEFINITIONS_H
#define TASK_DEFINITIONS_H

#define TASKSET_SIZE 40

typedef double time_instance;

// Structure for task
struct task {
    double T; // Period
    double C; // Computation time
    double D; // Deadline
    double u; // Utilisation
};

typedef struct task taskset[TASKSET_SIZE]; // Define the new type 'tasks'

#endif // TASK_DEFINITIONS_H
