# TP5 (MPI)

## Mise en place ssh
Pour pouvoir se connecter sur des machines sans utiliser de mot de passe, nous allons mettre en place le mécanisme de cléfs publique/privée de ssh.

1. Générez un couple de clef publique/privée avec la commande ssh-keygen -t rsa. Ne mettez pas de passphrase à moins que vous ne sachiez utiliser un ssh-agent.
2. Placez vous dans le répertoire $HOME/.ssh et copiez votre clef publique dans le fichier authorized_keys
3. Vérifiez que vous pouvez faire un ssh vers votre machine (ssh localhost) sans avoir à entrer de mot de passe. 

## MPI
Nous allons utiliser openMPI. Il est possible de l'installer avec yum sur Fedora ou [MacPorts](https://www.macports.org) sous OS X (vous devez déjà l'avoir installé avant le début du TP!):

    yum install openmpi-bin openmpi-doc libopenmpi-dev.

Il est aussi possible de compiler le code source mais c'est plus long.

Vérifiez qu'open MPI est bien installé sur votre machine. Pour cela regardez si l'exécutable mpicc (ou openmpicc) pour compiler vos programmes et mpirun (ou openmpirun) pour les exécuter sont disponibles.

## Hello world en MPI
1. Écrire un programme MPI qui affiche son numéro de rang et exécutez le pour un nombre variable de processus
2. Écrire un programme MPI tel que le premier processus affiche "hello", le deuxième affiche "goodbye" et les autres ne font rien. Vérifiez le comportement de votre programme dans le cas où vous l'éxécutez sur plus de 2 processeurs.

## Ping Pong
1. Écrire un programme MPI composé de deux processus. Le premier enverra un entier au second qui l'affichera. Les deux termineront ensuite.
2. Modifiez le programme précédent pour qu'il fonctionne quand il y a plus de 2 processus. Dans ce cas, le maitre devra envoyer les données autant de fois qu'il y a d'autres processus.

## Pipeline
1. Implémentez en MPI l'exemple de pipeline vu en cours

## Anneau
On considère une topologie en anneau basée sur le rang des processus. Chaque processus a un prédécesseur et un successeur dans l'anneau. MPI fournit des primitives pour créer des topologies virtuelles (e.g. MPI_Cart_*) mais nous n'allons pas les utiliser.
1. Si un processus a comme rang rank sur un anneau de size processus, quel est le rang de son prédécesseur et celui de son successeur
2. Ecrivez un programme MPI dont les processus sont organisés en anneau et où chaque processus demande à son prédécesseur son rang.
3. Ecrivez une nouvelle version de votre programme pour que le processus de rang 0 envoie un jeton (un entier) à son successeur, qui fera de même. Le programme s'arretera quand il aura fait un tour complet de l'anneau.
4. Ecrivez une nouvelle version de votre programme de sorte que le maitre envoie un tableau sur l'anneau. Ce tableau sera rempli par chaque processus qui y mettra l'heure à laquelle il a démarré.

## Deadlock
On considère un programme composé de deux processus ayant un code strictement identique. Chaque processus envoie un tableau à l'autre.
1. Testez votre programme pour des tailles variables de tableau (10, 100, 1000,...) et essayez de provoquer un deadlock
2. Comment expliquer que le deadlock n'apparait qu'à partir d'une certaine taille?