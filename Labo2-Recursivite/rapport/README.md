# Rapport 
## Nombre théorique de possibilités
Le calcul pour connaitre le nombre de possibilités est le suivant :

```
(9 * 4) * (8 * 4) * (7 * 4) * (6 * 4) * (5 * 4) * (4 * 4) * (3 * 4) * (2 * 4) * (1 * 4)
```
Car pour la première pièce nous avons
le choix parmi 9 pièces et pour chaque pièce, il y a ensuite le choix parmi 4
orientations différentes. Pour la deuxième pièce, nous avons le choix parmi les
huit pièces restantes et 4 orientations. Et ainsi de suite jusqu'à la dernière
pièce.
Ce qui donne "9! * 4<sup>9</sup>" = 95'126'814'720 possibilités.

## Comparaison : nombre d'appels théoriques et nombre d'appels effectués
Notre fonction fait 3767 appels récursifs contre les milliards d'appels nécessaires 
pour générer les 95'126'814'720 possibilités théoriques. Il y a une énorme différence
entre les deux nombres. Elle s'explique par le fait que lorsqu'on se rend compte
qu'une pièce ne peut pas être posée à cet endroit (à cause des symboles), on passe
directement à la possibilité suivante au lieu de continuer à poser des pièces dans
une configuration qui est déjà fausse.

## Solutions
Avec notre algorithme nous trouvons huit solutions qui sont les suivantes :
```
5c 3c 7c 8d 4d 2c 6d 9c 1a
9b 3c 8c 2c 6c 7c 4c 5b 1d
8d 7d 1a 3d 6d 5c 9c 2d 4d
1c 9a 6b 2a 4b 8b 7a 3a 5a
7d 2d 1b 3d 4a 9d 5d 8a 6a
6c 8c 5b 9b 4c 3b 1d 2b 7b
4b 2b 9a 5a 6b 3b 1c 7b 8b
1b 5d 4a 7a 6a 2a 8a 3a 9d
```
On remarque qu'il n'y a en fait que deux réelles solutions. En effet, les autres
solutions sont juste des rotations du puzzle tout entier. Chaque solution existe
sous 4 variantes différentes en fonction des orientations possibles.
On peut donc les classer ainsi : 
```
    Première variante                     Deuxième variante
5c 3c 7c 8d 4d 2c 6d 9c 1a            9b 3c 8c 2c 6c 7c 4c 5b 1d
6c 8c 5b 9b 4c 3b 1d 2b 7b            4b 2b 9a 5a 6b 3b 1c 7b 8b
1c 9a 6b 2a 4b 8b 7a 3a 5a            1b 5d 4a 7a 6a 2a 8a 3a 9d
7d 2d 1b 3d 4a 9d 5d 8a 6a            8d 7d 1a 3d 6d 5c 9c 2d 4d
```

Vous pouvez les observer sur les gif suivant.

Première variante : 

![Rotation du puzzle, solution 1](solution_1.gif)

Deuxième variante :

![Rotation du puzzle, solution 2](solution_2.gif)

## Analyse
Si l'on compare nos solutions au slogan du Djeco : 
```
"Des millions de possibilités et une seule solution !"
```
Il y a en réalité non pas une mais deux solutions (8 si l'on compte les rotations
comme des solutions différentes). La différence est très petite et non significative.
Cependant si l'on compare le nombre total de possibilités, on passe de
quelques millions dans le slogan à plus de 95 milliards dans la réalité. Le slogan
est donc totalement faux mais se justifie de deux manières différentes. 
La première raison est une raison commerciale. En effet, cela ferait un peu peur
de savoir qu'il y a autant de possibilités, surtout pour des petits enfants. La
seconde raison est que les créateurs du jeu ne se sont pas amusés à calculer le
nombre de possibilités et qu'ils ont mis "des millions" pour signifier le nombre
très important de possibilités.