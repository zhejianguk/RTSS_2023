#include <stdio.h>
#include <stdint.h>

struct task {
  double T;
  double C;
  double D;
  double u;
};

double dbf(struct task* h, double t) {
  double dbf_t;
  dbf_t = (((t - h->D) / h->T) + 1) * h->C;

  if (dbf > 0) {
    return dbf_t;
  } else {
    return 0;
  }
}

int main() {
  struct task task_1 = {5, 2, 5, 0.4};

  for (int i = 0; i < 10; i ++){
    double dbf_t = dbf(&task_1, i);
    printf("Debug: at time instance %i, %f \r\n", i, dbf_t);
  }


    
  return 0;
}
