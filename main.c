#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "definitions.h"
#include "bound.h"
#include "min_budget.h"
#include "interface_select.h"
#include "task_gen.h"

int main() {
  srand(time(NULL));

  
  taskset ts[NUM_CORES];
  capacity cap[NUM_CORES];
  double U_output[20];
  int U_counter = 0;
  int U_counter_End = 14;
  double U = 0.2;

  
  printf("\r\n=======================================================================================================================\r\n");
  printf("Testing the schedulability for a %d-core system under utilization from %.2f to %.2f. Number of Trails: %d \r\n", NUM_CORES, U, U+U_Factor*U_counter_End, HOW_MANY_TRAILS);
  printf("=======================================================================================================================\r\n");

  while (U_counter <= U_counter_End){
    double sucess_trails = 0;

    for (int trail = 0; trail < HOW_MANY_TRAILS; trail ++){
      uunifast_per_core(TASKSET_SIZE, U, ts);

      /* Print out information of the generated tasks */
      /*
      double U_all = 0;
      for (int core = 0; core < NUM_CORES; ++core) {
          double total_utilization = 0;
          for (int i = 0; i < ts[core].task_count; ++i) {
            printf("Task %d: Utilization = %.7f, Computation Time = %.7f, Period = %.7f, Deadline = %.7f\n",
                    i + 1, ts[core].tasks[i].u, ts[core].tasks[i].C, ts[core].tasks[i].T, ts[core].tasks[i].D);
            total_utilization += ts[core].tasks[i].u;
          }
          U_all = U_all + total_utilization;
          printf("The total utilization for Core %d is %f\n", core, total_utilization);
      }
      printf("The total utilization for system is %f\n",U_all);*/

      

      int s = interface_select_all(ts, cap);
      if (s == 0){
        // printf ("Trail %d: SUCCESS \r\n", trail);
        sucess_trails = sucess_trails + 1;
      } else {
        // printf ("Trail %d: FAIL \r\n", trail);
        sucess_trails = sucess_trails;
      }

      for (int core_idx = 0; core_idx < NUM_CORES; ++core_idx){
        // printf("Period = %f, Budget = %f \r\n", cap[core_idx].P, cap[core_idx].B);
      }
    }

    double success_ratio = sucess_trails / HOW_MANY_TRAILS;
    printf ("%d cores with %f utilisation, sucess_ratio: %f. \r\n", NUM_CORES, U, success_ratio);
    U_output[U_counter] = success_ratio; 
    
    U_counter++;
    U = U+U_Factor;
  }
    printf("=====================================================================================\r\n");
    printf ("Output for excel \r\n");
    for (U_counter = 0; U_counter <= U_counter_End; U_counter++){
      printf("%f\t", U_output[U_counter]);
    }


  return 0;
}





