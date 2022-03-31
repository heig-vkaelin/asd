# Rapport Labo 9 - Taquin

## Auteurs:
Jonathan Friedli, Valentin Kaelin et Lazar Pavicevic

## Tables des matières

* [Introduction](#Introduction)
* [Implementation](#Implementation)
* [NxN](#NxN)
* [3x3](#3x3)
* [4x4](#4x4)
* [Explications du coût mémoire](#Explications-du-coût-mémoire)
* [Explications de la complexité temporelle](#Explications-de-la-complexité-temporelle)

## Introduction

Le but de ce laboratoire est la création d'un programme permettant de résoudre, de la manière
la plus courte, un jeu du Taquin 3x3. Nous utilisons des graphes afin de résoudre ce problème.

Les mesures d'exécutions ont étés réalisées avec un processeur Intel i7 9700K et 
16GB de ram.

## Implementation

Au niveau de l'implémentation du graphe, nous avons décidé d'utiliser une 
liste chaînée simple pour stocker les sommets adjacents du sommet actuel. On 
s'assure alors des insertions en temps constant. Le graphe contient une liste de 
parents implémentée en tant que table de hachage non-ordonnée. Ce choix a permis 
de ne stocker que le hash et son parent plutôt que d'utiliser le sommet entier 
comme clé.

## NxN

* Nombre de sommets     : ```(N*N)! / 2```
* Complexité temporelle : ```O(N*N*M)```
* Coût mémoire          : ``` ~ 16 * N * N * (N * N)!``` (Pour un N grand)

## 3x3

* Nombre de sommets     : 9! / 2 = 181'440 (Seule la moitié des permutations sont 
  atteignables)
* Temps d'exécution     : Entre 10 et 620 ms selon le nombre d'étapes nécessaires  
* Coût mémoire          : ~ 20.8 MB

## 4x4

* Nombre de sommets     : 16! / 2 = ~ 1.05 * 10^13
* Coût mémoire          : Plus de d'1 PB => impensable à résoudre de cette manière



## Explications du coût mémoire
Nous n'avons pas pris en compte toutes les données du programme, seulement celles qui impactent le plus
le résultat final. Par exemple, les différentes string créées dans le programme ne sont comptées.

Le calcul est le suivant:
```
Taille d'un sommet * Nombre de sommets + Taille de la table de hachage non-ordonnée + Taille de la queue
```
### Pour du 3x3:
```
24 + 36 = 60 Bytes = Taille d'un sommet
```

Un sommet vide utilise 24 Bytes car il s'agit d'un vector de ```uint_32```.  
La longueur des vectors est représentée par la dimension du taquin au carré, ici
3x3 = 9.  
Chaque élément du vector est un ```unint_32``` donc 9 * 4 = 36 Bytes.

``` 
32 * 218'971 = 7'007'072 Bytes = ~ 7 MB = Taille de la table de hachage non-ordonnée
```
Avec ```bucket_count()``` nous obtenons le nombre de cases dans notre table de
hachage qui vaut 218'971.  
On multiplie le nombre de cases par 32 Bytes qui est la taille mémoire d'un
```size_t``` (le type de notre hash), de la taille de la map et de deux pointeurs.  
Pour la mémoire utilisée par les éléments, elle a déjà été prise en compte au début du calcul.

``` 
48 + 16 * (9!)/2 = 2'903'088 Bytes = ~ 2.9 MB = Taille de la queue
```
48 = 6 pointeurs d'une queue vide, 16 = taille d'un élément de la queue, (9!)/2 = nombre de sommets

Le résultat final nous donne donc:

```
60 * 181'440 + 7'007'072 + 2'903'088 = 20'796'560 Bytes = ~ 20.8 MB
```

### Pour du NxN:
```
24 + N * N * 4 = Taille d'un sommet
```

``` 
32 * ((N * N)!)/2 = Taille de la table de hachage non-ordonnée
```
Nous avons généralisé le ```bucket_count()``` au nombre de sommets car 
il est impossible de connaître le nombre exact de cases utilisées lors de l'exécution.

``` 
48 + 16 * ((N * N)!)/2 = Taille de la queue
```

Le résultat final nous donne donc:

```cpp
// Taille d'un sommet * Nombre de sommets + Taille de la table de hachage non-ordonnée + Taille de la queue
48 * N * N * ((N * N)!) + 32 * ((N * N)!) = 16 ((N * N)!) * (3 * (N * N) + 2) = ~16 * N * N * (N * N)!
```

## Explications de la complexité temporelle

```M``` = nombre de sommets  
```N``` = nombre de cases dans une ligne/colonne du jeu du Taquin  
### Fonctions:   
  getNeighbour():```O(N*N)```  
  parentsBFS(): ```O(N*M)```  
  searchSmallestChain(): ```O(N*N*M)```  
  création du hash : ```O(N*N)```  

### Total: 
  Algorithme en```O(N*N*M)```   
  Dans notre cas, N = 3 et M = 181'440.
