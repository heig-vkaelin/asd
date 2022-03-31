# Enoncé

Aucun code ne vous est fourni pour ce laboratoire.

Votre but est d'écrire un programme qui permette de trouver la solution la plus courte pour résoudre le jeu du taquin 3x3 disponible ici : [https://ocuisenaire.github.io/ASD1-Labs/taquin/](https://ocuisenaire.github.io/ASD1-Labs/taquin/).
* Les positions des pièces sont numérotées de 0 à 8.
* Votre programme reçoit en entrée les numéros des pièces aux positions 0 à 8.
* La pièce 0 est la case vide
* En sortie, votre programme fournit la liste des positions successives de la pièce qui se déplace.

La technique à utiliser consiste à modéliser le problème sous forme de graphe, puis à appliquer un algorithme de recherche de chemin le plus court par parcours en largeur de ce graphe.

En plus du code, vous devez rendre un mini-rapport au format markdown indiquant, en fonction de la taille n x n du taquin,

* Le nombre de sommets de votre graphe
* La complexité temporelle de votre algorithme
* Le coût en mémoire de votre solution
* Quelles seraient ces valeurs pour résoudre un [taquin 4x4](https://ocuisenaire.github.io/ASD1-Labs/taquin_4x4/).
