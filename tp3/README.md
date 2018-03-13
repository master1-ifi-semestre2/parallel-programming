# TP3 (OpenMP et Préfixe Parallèle)

## Exercice 1 (Parallel regions)
Le but de cet exercice est d'illustrer l'utilisation des régions parallèles dans opemp et leur relation avec les structures parallélisables comme la boucle for. L'ensemble de l'exercice est à faire dans un fichier C.

a) Écrivez une méthode `parallelRegion()` contenant un `printf(...)` dans une région parallele (`#pragma omp parallel`). Exécutez la avec un nombre variable de threads. Que remarquez vous ?

```c
void parallelRegion() {
  #pragma omp parallel
  {
    printf("numero %d threads.\n", omp_get_thread_num());
  }
}
```

b) Ajoutez une méthode `paralleRegionForOutside()` qui reprend le code de la méthode précédente en y ajoutant une boucle for (avec printf et sans aucun pragma) après la région parallele. Exécutez et commentez le résultat

```c
void paralleRegionForOutside() {
  #pragma omp parallel 
  {}
  for (int i=0; i < 10; i++) {
    printf("%d threads.\n", omp_get_thread_num());
  }
}
```

c) Ajoutez une méthode `parallelRegionForInside()` qui cette fois place le for à l'intérieur de la zone parallèle. Exécutez et commentez.

```c
void parallelRegionForInside() {
  #pragma omp parallel
  {
    for (int i=0; i < 10; i++) {
      printf("%d threads.\n", omp_get_thread_num());
    }
  }
}
```

d) Finalement, écrivez une méthode `parallelRegionForInsideWithPragma()` qui rajoute au code précédent `#pragma omp for`. Exécutez et commentez

```c
void parallelRegionForInsideWithPragma() {
  #pragma omp parallel
  {
    printf("%d threads--------.\n", omp_get_thread_num());
    #pragma omp for
    for(int i=0; i < 10; i++) {
      printf("%d threads.\n", omp_get_thread_num());
    }   
  }
}
```

## Exercice 2 (Portée lexicale et dynamique)
OpenMP utilise deux notions de portée. La première est dite lexical et ne contient que les lignes de programme contenues dans le bloc considéré. La deuxième, dite portée dynamique, comporte le code accesible dans le bloc ainsi que toutes les lignes accessibles depuis celui-ci (appels de méthodes, goto...). Le but de cet exercice est de constuire des exemples qui illustrent cette notion de portée dans deux situations : les variables privées et les constructions parallèles.

a) Écrivez un programme openMP contenant une variable globale `int` global et une méthode `privateScope0()` contenant une boucle for parallèle incrementant global. Quelle sera la valeur de global en entrée et en sortie de cette méthode ?

b) Écrivez une méthode `privateScope1()` faisant le même traitement, mais déclarant global comme variable privée à l'aide de l'option de pragma `private()`. Quel est le résultat?

c) Écrivez une méthode `privateScope2()` qui fait la même boucle for que dans la question précédente, mais délègue l'incrémentation de global à une méthode void `privateScope2_sub()`. Quel est le résultat? Qu'en concluez vous sur la portée de clause private ?

Suivant la version d'OpenMP, la valeur initiale et finale d'une variable privée peut être non définie. Pour éviter toute ambiguité, on peut utiliser les clauses `firstprivate()` et `lastprivate()`.

## Exercice 3 (Parallel prefix)
Nous allons implémenter le calcul des préfixes en parallèle en 3 phases, pour effectuer une somme sur les éléments d'un tableau. Le programme partira d'un tableau source initial de m données, construira les tableaux intermédiaires nécessaires et fournira le tableau final b tel que

    b[k] = source[0] + source[1] + ... + source[k]

L'algorithme sera implémenté en utilisant le squelette suivant :

```c
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
  //TODO : remplissage du tableau destination de taille 2*n en
  // copiant les données du tableau source dans destination, 
  // à la bonne position
  // on suppose que le malloc de destination a été fait avant
   
         
  // TODO: Boucle de calcul pour la montée dans l'arbre/tableau
}

void descente(struct tablo * a, struct tablo * b) {
  // TODO : implementation de la phase de descente
}

void final(struct tablo * a, struct tablo *b) {
  // TODO : phase finale
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
  montee(&source, a);
  printArray(a);

  struct tablo * b = allocateTablo(source.size*2);
  descente(a, b);
  printArray(b);
   
  final(a,b);
  printArray(b);
}
```