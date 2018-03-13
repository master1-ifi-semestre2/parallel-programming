# TP2 (introduction à OpenMP)
Pour écrire un programme openMP, il faut
    
    inclure <omp.h>
    compiler avec l'option -fopenmp

Mesurer les durées d'exécution peut se faire en utilisant la commande time du shell, le programme `time` (en général /usr/bin/time) ou l'API `gettimeofday()`.

En règle générale, il vaut mieux n'avoir qu'un unique code source qui sera compilé en deux exécutables, avec et sans OpenMP. Le code spécifique à OpenMP (hors pragma) peut être protégé par  `#ifdef _OPENMP` 

## Exercice 1 (parallélisme de boucle for)
On considère un tableau de n cases contenant chacune une valeur aléatoire.

1. Écrire un programme C qui lit la taille du tableau sur la ligne de commande, le crée et le remplit de valeurs aléatoires.
2. Ecrire une méthode carre(...) prenant le tableau en paramètre et elevant la valeur de chacune des cases au carré
3. Modifiez ce programme pour que les boucles for soient parallélisées par openMP
    1. Mesurez l'impact de la parallelisation de chaque boucle sur le temps d'exécution global
    2. Expliquez pourquoi il n'est pas efficace de paralléliser certaines boucles for. 
    3. Tracez le temps pris par la méthode  `carre()` en fonction de la taille du tableau.
4. Faites afficher par votre programme le nombre de threads qui sont crées par openMP. Que remarquez vous ?
5. Modifiez votre programme pour fixer le nombre de threads de la boucle for de 1 à 20. Dans chaque cas, mesurez le temps pris par votre programme (utilisez l'API de timing ou la commande `time)` et la fonction `carre()`. 
    1. Tracez la durée de la méthode `carre()` en fonction du nombre de threads
    2. Que constatez vous ?
6. Discutez de la répartition des temps passés en user space et en kernel space. Est-ce que cette répartition dépend des boucles parallélisées ?
7. Cherchez comment à l'aide de la variable OMP_NUM_THREADS il est possible de modifier le nombre de threads sans modifier votre code.

## Exercice 2 (Variables partagées et privées)
On veut profiter de la boucle de la méthode carre() pour faire la somme de tous les éléments du tableau.

1. Dans la méthode carre(...) précédente, déclarez une variable int total avant la boucle for et utilisez la pour faire la somme de toutes les cases du tableau dans la boucle. Que vaut total en sortie de boucle? pourquoi ?
2. Indiquez maintenant que total est une variable privée. Que vaut-elle en sortie de boucle? pourquoi ?
3. À l'aide d'une section critique, implémentez correctement la somme des éléments. Que constatez vous en terme de performances?
4. OpenMP permet de faire une opération de réduction sur une variable. Expliquez ce que cela signifie
5. Utilisez la clause de réduction pour arriver au même résultat et discutez les mérites de cette solution comparée à la précédente

## Exercice 3
Écrivez un programme parallèle de calcul du produit de 2 matrices.

## Exercice 4 (Blocs paralleles)
Pour cet exercice, inspirez vous du code Java du tri du TP1
1. Écrivez une version C mono-thread du tri fusion
2. Parallelisez cette version de de telle sorte que
    - le tableau initial est divisé en 2 sous tableau
    - ces 2 sous tableaux sont triés en parallèle
    - le résultat est fusionné pour donner le tableau final
3. Est-il possible d'introduire plus de parallélisme?