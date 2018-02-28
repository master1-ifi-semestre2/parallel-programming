#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Ne pas oublier d'inclure le fichier time.h

struct Array {
  int taille;
  int * donnee;
};

typedef struct Array Array;

Array * createTab(int n) {
  Array * tab = NULL;
  tab = malloc(sizeof(Array));
  tab->taille = n;
  tab->donnee = malloc(n*sizeof(int));
  return tab;
}

void initTab(Array * array) {
  int i;
  int nb_alea = 0;
  srand(time(NULL));// initialisation de rand
  #pragma omp parallel for
  for (i = 0; i < array->taille; i++) {
    nb_alea = rand();
    array->donnee[i] = nb_alea;
  }
}

void showTab(Array * array) {
  int i;
  printf("[");
  for (i = 0; i < array->taille; i++) {
    printf(" %d ", array->donnee[i]);
  }
  printf("]\n");
}

void carre(Array * array) {
  int i;
  #pragma omp parallel for
  for (i = 0; i < array->taille; i++) {
    array->donnee[i] = array->donnee[i]*array->donnee[i];
  }
}

int main(int argc, char** argv) {
  Array * array;
  int n;
  if (argc > 1) {
    n = atoi(argv[1]);
    array = createTab(n);
    printf("Taille du tableau %d \n", array->taille);
    initTab(array);
    //showTab(array);
    carre(array);
    //showTab(array);
  } else {
    printf("Manque la taille du tableau\n");
  }
  free(array);
  return 0;
}

