# Projet: Déplacements dans un univers virtuel

## 1. Objectifs

- Résoudre un problème simple.
- Analyser la complexité temporelle d'un algorithme.
- Pratiquer l'encapsulation et concevoir des types abstraits de données.
- Gérer la mémoire.

## 2. Description du projet

Dans ce travail pratique, vous devez implémenter un agent (ex.: un robot) qui explore un univers constitué de salles liées par des portails (ou téléporteurs).

Chaque salle est identifiée par un numéro (son indice dans le tableau de salles) et composée de cellules. Une cellule est caractérisée par ses coordonnées, c'est-à-dire un triplet d'entiers: le numéro de la salle dans laquelle elle se trouve ainsi que sa position (i,j) dans la salle. Il existe trois types de salles, selon leur forme : carré, diamant ou triangle. La forme d'une salle donnée est déterminée par le nombre de cellules et leur disposition. Un paramètre d'entrée n (entier) donne les dimensions d'une salle, selon sa forme. À titre d'exemple, la figure ci-dessous illustre les salles carre 4 (Salle 0), diamant 5 (Salle 1) et triangle 7 (Salle 2). Notez que n doit être impair pour les salles de type Diamant et Triangle (ce sera toujours le cas dans les tests) mais peut être pair ou impair pour les carrés. Une salle de type triangle est toujours orientée comme dans l'image, c'est-à-dire que la "pointe" du triangle (position (3,3) dans la figure 1) est toujours dirigée vers le bas. 
