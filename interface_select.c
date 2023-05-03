#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "definitions.h"
#include "bound.h"
#include "min_budget.h"

double others_utilization (taskset *ts, int core_idx){
  double others_utilization = 0;
  for (int i = 0; i < NUM_CORES; ++i) {
    if (i != core_idx) {
      others_utilization += ts[i].U;
    }
  }

  return others_utilization;
}

double min_period(taskset *ts, int core_idx) {
    double others_utilization_t = others_utilization(ts, core_idx);
    double min_period_t = (ceil(1/(1 - others_utilization_t)))*q;
    return min_period_t;
}

double max_period(taskset *ts, int core_idx) {
  double min_D_C_t = min_D_C(ts[core_idx]);
  double others_utilization_t = others_utilization(ts, core_idx);

  double max_period_t = floor(min_D_C_t / (q*2*others_utilization_t))*q;
  return max_period_t;
}

double interface_select (taskset *ts, int core_idx, capacity* cap){
  double period = 0;
  double budget = 0;
  double min_period_t = min_period(ts, core_idx);
  double max_period_t = max_period(ts, core_idx);

  double w_i = 0x7FFFFFFF;
  double pi = min_period_t;

  while (pi <= max_period_t){
    double theata = min_budget(&ts[core_idx], pi);

    if (theata != -1){
      if (theata/pi < w_i) {
        w_i = theata/pi;
        period = pi;
        budget = theata;
      }
    }
    pi = pi + q;
  }
  
  cap[core_idx].P = period;
  cap[core_idx].B = budget;


  return w_i;
}


int interface_select_all (taskset *ts, capacity* cap){

  int sucess = 0;

  int c = 0;
  while (c < NUM_CORES){
    int interface_select_t = interface_select(ts, c, cap);
    if (interface_select(ts, c, cap) == 0x7FFFFFFF){
      return -1;
    } else {
      c = c + 1;
    }
  }

  double total_bandwith_t = total_bandwidth(cap);
  // printf("total_bandwith_t = %f \r\n", total_bandwith_t);


  return ((total_bandwith_t <= 1) && (total_bandwith_t > 0)) ? 0 : -1;
}
