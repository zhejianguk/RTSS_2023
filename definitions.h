#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define NUM_CORES 4
#define TASKSET_SIZE 4
#define q 4

typedef double time_instance;

// Structure for task
typedef struct {
    double T; // Period
    double C; // Computation time
    double D; // Deadline
    double u; // Utilisation
} task;

typedef struct {
    int task_count;
    task tasks[TASKSET_SIZE];
    double U; // New field to store the total utilization
} taskset;


typedef struct {
    double P; // Period
    double B; // Budget 
    double w;
} capacity;


#endif // TASK_DEFINITIONS_H
