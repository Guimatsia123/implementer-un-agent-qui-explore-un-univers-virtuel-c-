/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    TP2 -- http://cria2.uqam.ca/INF3105/tp2
    © Jaël Champagne Gareau.
    MARIUS GUIMATSIA AKALONG GUIM27309006
    SENAYAH KOSSIWA SENK14299107
*/

#include "salle.h"

#include <cassert>
#include <iostream>

using namespace std;

Coordonnees::Coordonnees(int _salle, int _ligne, int _colonne)
: salle(_salle), ligne(_ligne), colonne(_colonne) {}

int Coordonnees::getSalle() const {
  return salle;
}

bool Coordonnees::operator==(const Coordonnees& c) const {
  // À compléter
  return salle == c.salle && ligne == c.ligne && colonne == c.colonne;
}

istream& operator>>(istream& is, Coordonnees& c) {
 
    char ignore; // Pour ignorer les characteres (,)
    int sal, lig,col;
   // is >> c.salle >> ignore >> c.ligne >> ignore >> c.colonne >> ignore;
     is >> sal >> ignore >> lig >> ignore >> col >> ignore;
     //if(isdigit(sal) && isdigit(lig) && isdigit(col)){
      c.salle = sal;
      c.ligne = lig;
      c.colonne = col;
    // }

    return is;
  }

  Salle::Salle() {}

  Salle::Salle(const string& nomType, int _dimension) : dimension(_dimension) {
    if (nomType == "carre")
      type = Carre;
    else if (nomType == "diamant")
      type = Diamant;
    else if (nomType == "triangle")
      type = Triangle;
    else
      assert(false && "nomType est invalide");

    for (int i = 0; i < obtenirNbCases(); ++i)
      cellules.ajouter(Cellule());

  }
  Salle::~Salle() {
}

  bool Salle::estPositionValide(const Coordonnees& p) const {
    return obtenirIndice(p.ligne, p.colonne) != -1;
  }

  const Coordonnees& Salle::obtenirPortail(const Coordonnees& p) const {
    return cellules[obtenirIndice(p.ligne, p.colonne)].portail;
  }

  bool& Salle::marqueurVisite(const Coordonnees& p) const {
    return cellules[obtenirIndice(p.ligne, p.colonne)].visite;
  }

// Mettre tous les marqueurs visite a false
  void Salle::initialiseMarqueurVisite() const {
   for (int i = 0; i < obtenirNbCases(); ++i)
    cellules[i].visite = false;
}

// Marqueur pour signifier qu'une cellule est deja visitee

void Salle::dejaVisite(const Coordonnees& p) const {
 cellules[obtenirIndice(p.ligne, p.colonne)].visite = true;
}

void Salle::nonVisite(const Coordonnees& p) const {
 cellules[obtenirIndice(p.ligne, p.colonne)].visite = false;
}

void Salle::placerPortailCellule(const Coordonnees& de,
 const Coordonnees& vers) {
  cellules[obtenirIndice(de.ligne, de.colonne)].portail = vers;
}



int Salle::obtenirNbCases() const {
  if (type == Carre)
    return dimension * dimension;

  else if (type == Diamant) {
    int nbCase = dimension;
    int temp = dimension;
    for (int i = 1; i <= dimension/2; ++i){
     temp = temp - 2;
     nbCase = nbCase + temp; 
   }
   return ((nbCase*2) - dimension);
 }

 else if (type == Triangle) {
  int nbCase = dimension;
  int temp = dimension;
  for (int i = 1; i <= dimension/2; ++i){
   temp = temp - 2;
   nbCase = nbCase + temp; 
 }
 return nbCase;
}

  return -1;  // Erreur
}

int Salle::obtenirIndice(int ligne, int colonne) const {
  if (type == Carre) {
    if (ligne < 0 || ligne >= dimension || colonne < 0 || colonne >= dimension)
      return -1;
    return (ligne * dimension) + colonne;
  } else if (type == Diamant) {

    
    int idebut = dimension/2;
    int colDeb = -1;
    int colFin = dimension;
    int indice = (dimension/2) * (dimension/2);
    if (ligne < 0 ||  ligne > dimension || colonne < 0 || colonne >= dimension)
      return -1;

    // bas du diamant

    if (ligne >= idebut) {
      int dim = dimension;
      for (int i = idebut; i < dimension; ++i) {
        colDeb++;
        colFin--;
        if (colonne >= colDeb && colonne <= colFin && ligne == i){
          return (indice + colonne - i + idebut);
        }
        indice += dim;
        dim -= 2;
      }
    } else {

      // haut du diamant

      int dim = dimension;
      dim -= 2;
      int indiceHaut= (dimension/2) * (dimension/2) - dim;
      int soustracttion = 0;
      for (int i = idebut-1; i >= 0; --i) {
        colDeb++;
        colFin--;
        soustracttion++;
        if (colonne >= colDeb && colonne <= colFin && ligne == i){
          return (indiceHaut + colonne - soustracttion );
        }

        dim -= 2;
        indiceHaut -= dim;
      }
    }

  } else if (type == Triangle) {
    int dim = dimension;
    int ifin = dimension/2;
    int colDeb = -1;
    int colFin = dimension;
    int indice = 0;
    if (ligne < 0 ||  ligne > ifin || colonne < 0 || colonne >= dimension)
      return -1;

    for (int i = 0; i <= ifin; ++i) {
      colDeb++;
      colFin--;
      if (colonne >= colDeb && colonne <= colFin && ligne == i){
        return (indice + colonne - i);
      }
      indice += dim;
      dim -= 2;
    }
  }

  return -1;  // type invalide
}



