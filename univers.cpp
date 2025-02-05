/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    TP2 -- http://cria2.uqam.ca/INF3105/tp2
    © Jaël Champagne Gareau.
    MARIUS GUIMATSIA AKALONG GUIM27309006
    SENAYAH KOSSIWA SENK14299107
*/

#include "univers.h"

#include <cassert>

using namespace std;
int nbChemins ;

void Univers::nombreCheminsRec(const Coordonnees& depart, const Coordonnees& arrivee) const{


  if(depart == arrivee)
    nbChemins++;
  else{

    // On recupere tous les voisins de la cellule depart.
    Tableau<Coordonnees> voisins;
    //(i-1,j), (i+1,j), (i,j-1) et (i,j+1), 

    Coordonnees v1, v2, v3, v4;

    //voisins v1
    v1.salle = depart.salle;
    v1.ligne = depart.ligne -1;
    v1.colonne = depart.colonne;

    // voisins v2
    v2.salle = depart.salle;
    v2.ligne = depart.ligne + 1;
    v2.colonne = depart.colonne;
    // voisins v3
    v3.salle = depart.salle;
    v3.ligne = depart.ligne ;
    v3.colonne = depart.colonne - 1;
    // voisins v4
    v4.salle = depart.salle;
    v4.ligne = depart.ligne;
    v4.colonne = depart.colonne + 1;


      //On ajoute un voisins dans la liste de voisins s'il se trouve dans un indice valide
    if(salles[v1.getSalle()].estPositionValide(v1))
      voisins.ajouter(v1);
    if(salles[v2.getSalle()].estPositionValide(v2))
      voisins.ajouter(v2);
    if(salles[v3.getSalle()].estPositionValide(v3))
      voisins.ajouter(v3);
    if(salles[v4.getSalle()].estPositionValide(v4))
      voisins.ajouter(v4);

      // Si la cellule de depart est un portail on lui aajoute le voisins qui mene vers la cellule de l'autre salle.
    if( salles[depart.getSalle()].obtenirPortail(depart).salle != -1)
      voisins.ajouter(salles[depart.getSalle()].obtenirPortail(depart));


    for (int i = 0; i < voisins.taille(); ++i){
      if(salles[voisins[i].getSalle()].marqueurVisite(voisins[i]) == false ){
        // v.visite = true
        salles[voisins[i].getSalle()].dejaVisite(voisins[i]);
        nombreCheminsRec(voisins[i], arrivee);
        // v.visite = false
        salles[voisins[i].getSalle()].nonVisite(voisins[i]);

      }

    }

  }

}

int Univers::calculerNombreChemins(const Coordonnees& depart,
 const Coordonnees& arrivee) const {
  // À compléter
  // Initialise tous les marqueurs visite a false pour toutes les salles de l'univers
  for(int i = 0; i < salles.taille(); i++){
    salles[i].initialiseMarqueurVisite();
  }
  if(salles[depart.getSalle()].estPositionValide(depart) && salles[arrivee.getSalle()].estPositionValide(arrivee)){
    nbChemins = 0;

    // l'indice de la cellule depart a true pour dire qu'elle a deja ete visite.
    salles[depart.getSalle()].dejaVisite(depart);
    
    nombreCheminsRec(depart, arrivee);
    return nbChemins;
  }

  return -1;
  
}


istream& operator>>(istream& is, Univers& univers) {
  int i = 0;
  while (true) {
    string type;
    is >> type;
    if (type == "-----") break;  // fin de la lecture des types de salle

    int dim;
    is >> dim;

   //Salle *salle = new Salle(type,dim);
    Salle salle(type, dim);

    univers.salles.ajouter(salle);
    i++;
  }

  // Lecture des portails
  while (!(is >> ws).eof()) {
    Coordonnees c1, c2;

    is >> c1;

    string fleche;
    is >> fleche;
    assert(fleche == "<-->");

    is >> c2;

    univers.salles[c1.getSalle()].placerPortailCellule(c1,c2);
    univers.salles[c2.getSalle()].placerPortailCellule(c2,c1);
  }

  return is;
}
