# TP3 (OpenMP et Préfixe Parallèle)

## Exercice 1 (Parallel regions)
Le but de cet exercice est d'illustrer l'utilisation des régions parallèles dans opemp et leur relation avec les structures parallélisables comme la boucle for. L'ensemble de l'exercice est à faire dans un fichier C.

a) Écrivez une méthode parallelRegion() contenant un printf(...) dans une région parallele (#pragma omp parallel). Exécutez la avec un nombre variable de threads. Que remarquez vous ?

```c
void parallelRegion() {
  #pragma omp parallel
  {
    printf("numero %d threads.\n", omp_get_thread_num());
  }
}
```

b) Ajoutez une méthode paralleRegionForOutside() qui reprend le code de la méthode précédente en y ajoutant une boucle for (avec printf et sans aucun pragma) après la région parallele. Exécutez et commentez le résultat

```c
void paralleRegionForOutside() {
  #pragma omp parallel 
  {}
  for (int i=0; i < 10; i++) {
    printf("%d threads.\n", omp_get_thread_num());
  }
}
```

c) Ajoutez une méthode parallelRegionForInside() qui cette fois place le for à l'intérieur de la zone parallèle. Exécutez et commentez.

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

d) Finalement, écrivez une méthode parallelRegionForInsideWithPragma() qui rajoute au code précédent #pragma omp for. Exécutez et commentez

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

a) Écrivez un programme openMP contenant une variable globale int global et une méthode privateScope0() contenant une boucle for parallèle incrementant global. Quelle sera la valeur de global en entrée et en sortie de cette méthode ?

```c
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
```

b) Écrivez une méthode privateScope1() faisant le même traitement, mais déclarant global comme variable privée à l'aide de l'option de pragma private(). Quel est le résultat?

```c
void privateScope1() {
  global = 0;
#pragma omp parallel for private(global)
  for (int i = 0; i < 10; i++) {
    global++;
    printf("in = %d\n", global);
  }
}
```

c) Écrivez une méthode privateScope2() qui fait la même boucle for que dans la question précédente, mais délègue l'incrémentation de global à une méthode void privateScope2_sub(). Quel est le résultat? Qu'en concluez vous sur la portée de clause private ?

```c
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
```

Suivant la version d'OpenMP, la valeur initiale et finale d'une variable privée peut être non définie. Pour éviter toute ambiguité, on peut utiliser les clauses firstprivate() et lastprivate().