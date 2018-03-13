#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

/**
Methode qui affiche le nombre de threads
 */
void parallelRegion() {
  #pragma omp parallel
  {
    printf("numero %d threads.\n", omp_get_thread_num());
  }
}

/**
Methode qui affiche le 
 */
void paralleRegionForOutside() {
  #pragma omp parallel 
  {}
  int i;
  for (i=0; i < 10; i++) {
    printf("%d threads.\n", omp_get_thread_num());
  }
}

void parallelRegionForInside() {
  #pragma omp parallel
  {
    int i;
    for (i=0; i < 10; i++) {
      printf("%d threads.\n", omp_get_thread_num());
    }
  }
}

/**
Execute repartie le taf sur les differents threads
 */
void parallelRegionForInsideWithPragma() {
  #pragma omp parallel
  {
    printf("%d threads--------.\n", omp_get_thread_num());
    int i;
    #pragma omp for
    for(i=0; i < 10; i++) {
      printf("%d threads.\n", omp_get_thread_num());
    }   
  }
}

int main(int argc, char** argv) {
  printf("*** Parallel regions ***\n");
  //printf("Q a)\n");
  //parallelRegion();
  //printf("Q b)\n");
  //paralleRegionForOutside();
  //printf("Q c)\n");
  //parallelRegionForInside();
  printf("Q d)\n");
  parallelRegionForInsideWithPragma();
}