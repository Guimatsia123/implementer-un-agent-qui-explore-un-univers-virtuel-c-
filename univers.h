/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    TP2 -- http://cria2.uqam.ca/INF3105/tp2
    © Jaël Champagne Gareau.
    MARIUS GUIMATSIA AKALONG GUIM27309006
    SENAYAH KOSSIWA SENK14299107
*/

#ifndef UNIVERS_H
#define UNIVERS_H

#include <iostream>

#include "salle.h"
#include "tableau.h"

class Univers {
 public:
  void nombreCheminsRec(const Coordonnees& depart, const Coordonnees& arrivee) const;
  int calculerNombreChemins(const Coordonnees&, const Coordonnees&) const;

  friend std::istream& operator>>(std::istream&, Univers&);

 private:
  // À compléter
    Tableau<Salle> salles;
};

#endif
