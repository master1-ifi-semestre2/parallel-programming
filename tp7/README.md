# TP7 - Map-Reduce

## WordCount et compagnie en local

[WordCount](https://hadoop.apache.org/docs/r1.2.1/mapred_tutorial.html) est un exemple de base de calcul MapReduce. Il est très facile à comprendre et à exécuter. 
1. Si ce n'est pas déjà fait, vérifiez que votre installation locale de Hadoop fonctionne bien (voir [ici](http://hadoop.apache.org/docs/r1.2.1/single_node_setup.html) )
2. Copiez le code d'exemple de WordCount, créez un jar et exécutez sur votre installation Hadoop. Comme donneé d'entrée, prenez n'importe quel fichier texte. 
3. Écrivez une programme MoreThan2 qui affiche les mots qui apparaissent au moins 2 fois dans le fichier initial

## Analyse de logs Web
On veut analyser des fichiers de [log](http://ita.ee.lbl.gov/html/contrib/NASA-HTTP.html) Apache d'un serveur Web de la NASA. Le but de cet exercice est d'écrire un ou des programmes MapReduce qui répondent aux questions   suivantes :

1. Combien chaque client (host) a-t-il fait de requêtes ?
2. Quel est l' ensemble des requêtes de chaque client? 
3. Quelle est la page web la plus demandée ?