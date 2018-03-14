#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>

struct tablo {
  int * tab;
  int size;
};

void printArray(struct tablo * tmp) {
  printf("---- Array of size %i ---- \n", tmp->size);
  int size = tmp->size;
  int i;
  for (i = 0; i < size; ++i) {
    printf("%i ", tmp->tab[i]);
  }
  printf("\n");
}

struct tablo * allocateTablo(int size) {
  struct tablo * tmp = malloc(sizeof(struct tablo));
  tmp->size = size;
  tmp->tab = malloc(size*sizeof(int));
  return tmp;
}

void montee(struct tablo * source, struct tablo * destination) {
//DONE : remplissage du tableau destination de taille 2*n en
  int i, j, l;
  for (i = 0; i < source->size; i++) {
    destination->tab[source->size +i] = source->tab[i];
  }
  // copiant les données du tableau source dans destination, 
  // à la bonne position
  // on suppose que le malloc de destination a été fait avant

  // DONE: Boucle de calcul pour la montée dans l'arbre/tableau
  for (l = log2(source->size) - 1; l >= 0; l--) {
    for (j = pow(2, l); j <= pow(2, l + 1) - 1; j++) {
      destination->tab[j] = destination->tab[2*j] + destination->tab[(2*j)+1];
    }
  }
}

void descente(struct tablo * a, struct tablo * b) {
  // DONE : implementation de la phase de descente
  b->tab[1] = 0;
  for (int i = 1; i <= log2(a->size/2); i++) {
    int j;
    int pow1 = pow(2, i);
    int pow2 = pow(2, i + 1) - 1;
    #pragma omp for
    for (j = pow1; j <= pow2; j++) {
      if (j%2 == 0) {
        b->tab[j] = b->tab[j/2];
      } else {
        b->tab[j] = b->tab[j/2] + a->tab[j-1];
      }
    }
  }
}

void final(struct tablo * a, struct tablo *b) {
  // DONE : phase finale
  int i;
  int logTab = log2(a->size/2);
  int pow1 = pow(2, logTab);
  int pow2 = pow(2, logTab + 1) - 1;
  #pragma omp for
  for (i = pow1; i <= pow2; i++) {
    b->tab[i] = b->tab[i] + a->tab[i];
  }
}

void generateArray(struct tablo * s) {
  //construction d'un tableau pour tester
  s->size=8;
  s->tab=malloc(s->size*sizeof(int));
  s->tab[0]=3;
  s->tab[1]=1;
  s->tab[2]=7;
  s->tab[3]=0;
  s->tab[4]=4;
  s->tab[5]=1;
  s->tab[6]=6;
  s->tab[7]=3;

}

int main(int argc, char **argv) {
  struct tablo source;

  generateArray(&source);

  struct tablo * a = allocateTablo(source.size*2);
  a->tab = malloc(source.size*2*sizeof(int));
  a->size = source.size*2;
  montee(&source, a);
  printArray(a);

  struct tablo * b = allocateTablo(source.size*2);
  b->tab = malloc(source.size*2*sizeof(int));
  b->size = source.size*2;
  descente(a, b);
  printArray(b);
   
  final(a,b);
  printArray(b);
}
