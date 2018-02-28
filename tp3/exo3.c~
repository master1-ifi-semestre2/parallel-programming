#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int global = 0;

void privateScope0() {
  printf("start = %d\n", global);
  #pragma omp parallel for
  for (int i = 0; i < 100000000; i++) {
    global++;
    printf("in = %d\n", global);
  }
  printf("global = %d\n", global);
}

void privateScope1() {
  global = 0;
#pragma omp parallel for private(global)
  for (int i = 0; i < 10; i++) {
    global++;
    printf("in = %d\n", global);
  }
}

void privateScope2_sub();

void privateScope2() {
  global = 0;
#pragma omp parallel for private(global)
  for (int i = 0; i < 10; i++) {
    void privateScope2_sub();
    printf("in = %d\n", global);
  }
}

void privateScope2_sub() {
  global++;
}

int main(int argc, char** argv) {
  printf("*** Parallel regions ***\n");
  //printf("Q a)\n");
  //privateScope0();
  //printf("Q b)\n");
  //privateScope1();
  //printf("Q c)\n");
  privateScope2();
}
