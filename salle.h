/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    TP2 -- http://cria2.uqam.ca/INF3105/tp2
    © Jaël Champagne Gareau.
*/

#ifndef SALLE_H
#define SALLE_H

#include <iostream>
#include <string>

#include "tableau.h"

enum TypeSalle {

  Carre,
  Diamant,
  Triangle,
};

class Coordonnees {
 public:
  Coordonnees(int _salle = -1, int _ligne = -1, int _colonne = -1);

  int getSalle() const;

  bool operator==(const Coordonnees&) const;

  // Format: (s, i, j)
  friend std::istream& operator>>(std::istream&, Coordonnees&);

  friend class Salle;
  friend class Univers;

 private:
  int salle;
  int ligne;
  int colonne;
};

class Salle {
  struct Cellule;

 public:
  Salle();
  Salle(const std::string& nomType, int _dimension);
  ~Salle();
 public:
  bool estPositionValide(const Coordonnees&) const;
  const Coordonnees& obtenirPortail(const Coordonnees&) const;
  void placerPortailCellule(const Coordonnees& de, const Coordonnees& vers);

  bool& marqueurVisite(const Coordonnees&) const;

 private:
  // Donne la position (indice) dans le tableau `cellules` correspondant
  // à la position (ligne, colonne) dans la salle
  int obtenirIndice(int ligne, int colonne) const;  // -1 -> position invalide

  // Retourne le nombre de cases valides de la salle
  int obtenirNbCases() const;

  // Met le marqueur visite a true
  void dejaVisite(const Coordonnees& p) const;

  // Met le marqueur visite a false
  void nonVisite(const Coordonnees& p) const;

  // Mettre tous les marqueurs visite a false
  void initialiseMarqueurVisite() const;
  // Retourne tous les voisins valide d'une cellule
    Tableau<Coordonnees>& obtenirVoisins(const Coordonnees& p) const;

  // Attributs (vous pouvez en ajouter d'autres si nécessaire)
  TypeSalle type;
  int dimension;
  Tableau<Cellule> cellules;

  // Un univers contient des Salles. Il est donc logique que la classe
  // Salle soit amie avec la classe Univers
  friend class Univers;
private:
  struct Cellule {
    // Mot clé mutable: un attribut mutable peut être modifié même si l'objet est const.
    mutable bool visite = false;
    Coordonnees portail;  // initialisé à {-1, -1, -1}
  };
};

#endif
