#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "definitions.h"
#include "bound.h"

int min_budget(taskset *ts, double Given_Period) {

    double lo = 1;
    double hi = Given_Period / q;
    capacity cap_t;
    cap_t.P = Given_Period;
    cap_t.B = Given_Period;

    if (schedulability_test(ts, &cap_t) == -1){
        // printf("================ Unschedule ================ \r\n");
        // printf("================ Min-Budget ================ \r\n");
        return -1;
    }

    while (lo < hi){
        double mid = floor((lo + hi)/2);
        cap_t.B = mid * q;
        if (schedulability_test(ts, &cap_t) == 0){
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    double min_budget = hi * q;
    return min_budget;
}
