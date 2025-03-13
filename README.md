# Pipex

Pipex est un projet en C permettant de reproduire le comportement d'un pipeline Unix en utilisant des processus et des redirections de fichiers.

## Installation

Pour compiler `pipex`, utilisez la commande suivante :

```sh
gcc -Wall -Wextra -Werror pipex.c pipex_utils.c -o pipex
```

## Utilisation

La syntaxe de `pipex` est la suivante :

```sh
./pipex infile "cmd1" "cmd2" outfile
```

- `infile` : Fichier d'entrée
- `cmd1` : Première commande exécutée
- `cmd2` : Deuxième commande exécutée
- `outfile` : Fichier de sortie

Exemple :

```sh
./pipex input.txt "grep hello" "wc -l" output.txt
```

Cela équivaut à la commande shell suivante :

```sh
< input.txt grep hello | wc -l > output.txt
```

## Fonctionnalités implémentées

- Utilisation des `pipe()` et `fork()` pour créer un pipeline entre deux commandes
- Redirections des entrées/sorties via `dup2()`
- Gestion des erreurs basiques

## Bonus : Gestion des pipelines multiples et here_doc

La version bonus ajoute les fonctionnalités suivantes :

### Pipelines multiples

Syntaxe :

```sh
./pipex infile "cmd1" "cmd2" "cmd3" ... "cmdN" outfile
```

Exemple :

```sh
./pipex input.txt "grep error" "sort" "uniq" output.txt
```

Ce qui équivaut à :

```sh
< input.txt grep error | sort | uniq > output.txt
```

### Here_doc

Permet d'utiliser un `here_doc` comme entrée au lieu d'un fichier. 

Syntaxe :

```sh
./pipex here_doc LIMITER "cmd1" "cmd2" ... "cmdN" outfile
```

Exemple :

```sh
./pipex here_doc END "cat" "wc -l" output.txt
```

L'entrée utilisateur sera lue jusqu'à ce que `END` soit tapé, puis transmise aux commandes.
