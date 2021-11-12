# Projet Supercomputing

## Environnement de Travail

### Packages nécessaires
- `Make`
- `gcc`

### Compilation
Le développement a été réalisé sur Linux, et le programme s'exécute sur Linux. Afin de compiler le projet, la commande est la suivante.
```
make
```
Un Makefile est présent dans la racine, qui permet de lancer les différentes commandes `gcc` de build.

### Execution
La commande pour exécuter le projet est 
```
./prog
```

### Options gcc utilisées
- -lpthread : pthread
- -lm : librairie mathématique
- -mavx/mavx2 : calcul vectoriel
- -Wall : Montre tous les warnings
- -ansi
- -pedantic : Ne compile pas si le code ne suit pas une norme

## Fichiers

Les différents exercices sont séparés en plusieurs fichiers 
- main.c : La fonction main lance les différents exercices
- exo1.c : Fonction de l'exercice 1 + test unitaire
- exo2.c : Fonction de l'exercice 2 + test unitaire
- exo3.c : Fonctions de l'exercice 3 + test unitaire
- utils.c : Fonctions utilitaires (horloge système, moyenne, écart-type, moyenne des temps sur K exécutions...)
