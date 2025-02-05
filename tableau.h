/* Squelette pour classe générique Tableau<T>.
 * TP1 -- Tableau dynamique générique
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 */

#ifndef TABLEAU_H_3105
#define TABLEAU_H_3105

#include <cassert>

template<class T>
class Tableau {
public:
  // Constructeurs
  Tableau(int capacite_initiale = 4);
  Tableau(const Tableau&);
  ~Tableau();

  // Fonctions de modifications
  void ajouter(const T& element);  // Ajouter un element à la fin
  void vider();
  void agrandir();
  // Insère element à position index. Les éléments à partir de index sont décalés d'une position.
  void inserer(const T& element, int index = 0);
  // Enlève l'element à position index. Les éléments après index sont décalés d'une position.
  void enlever(int index = 0);
  void enlever_dernier();

  // Fonctions utilitaires
  bool vide() const;
  int taille() const;
  int chercher(const T& element) const;  // Si non trouvé, retourne -1.
  bool contient(const T& element) const;

  // Opérateurs d'accès
  const T& operator[](int index) const;
  T& operator[](int index);

  // Opérateurs
  bool operator==(const Tableau<T>& autre) const;
  Tableau<T>& operator=(const Tableau<T>& autre);

private:
  T* elements;
  int nbElements;
  int capacite;
};

// ---------- Définitions, modèles de -------------
// En C++, les définitions sont habituellement dans des fichiers sources .cpp.
// Les classes "template" sont souvent une exception à cette règle.
// Ces modèles devant être instanciés, on les mets dans un fichier .h.

template<class T>
Tableau<T>::Tableau(int capacite_initiale):nbElements(0), capacite(capacite_initiale) {
  elements = new T[capacite = capacite_initiale]; 
}

template<class T>
Tableau<T>::Tableau(const Tableau& autre):nbElements(autre.nbElements), capacite(autre.capacite) {
  elements = new T[capacite];
  for (int i = 0; i < nbElements; ++i){
    elements[i] = autre.elements[i];
  }
}

template<class T>
Tableau<T>::~Tableau() {
  delete[] elements;
}

template<class T>
void Tableau<T>::agrandir() {
  if (nbElements == capacite){
    capacite *= 2;
    T* newTab = new T[capacite];
    for (int i = 0; i < nbElements; i++) {
      newTab[i] = elements[i];
    }
    delete[] elements;
    elements = newTab;
  }
}

template<class T>
void Tableau<T>::ajouter(const T& item) {
  agrandir();
  elements[nbElements++] = item;
}

template<class T>
void Tableau<T>::vider() {
  nbElements = 0;
}

template<class T>
void Tableau<T>::inserer(const T& element, int index) {
  assert(index >= 0 && index < nbElements);
  agrandir();
  for (int i = nbElements; i > index; --i)
    elements[i] = elements[i-1];
  nbElements++;
  elements[index] = element;
}

template<class T>
void Tableau<T>::enlever(int index) {
  assert(index >= 0 && index < nbElements);
  for (int i = index; i < nbElements; ++i)
    elements[i] = elements[i+1];
  --nbElements;
}

template<class T>
void Tableau<T>::enlever_dernier() {
  --nbElements;
}

template<class T>
bool Tableau<T>::vide() const {
  return nbElements == 0;
}

template<class T>
int Tableau<T>::taille() const {
  return nbElements;
}

template<class T>
int Tableau<T>::chercher(const T& element) const {
  for (int i = 0; i < nbElements; ++i) {
    if(elements[i] == element) return i;
  }
  return -1;
}

template<class T>
bool Tableau<T>::contient(const T& element) const {
  return chercher(element) != -1;
}

template<class T>
const T& Tableau<T>::operator[](int index) const {
  assert(index >= 0 && index < nbElements);
  return elements[index];
}

template<class T>
T& Tableau<T>::operator[](int index) {
  assert(index >= 0 && index < nbElements);
  return elements[index];
}

template<class T>
bool Tableau<T>::operator==(const Tableau<T>& autre) const {
  if (this == &autre) return true;
  if (nbElements != autre.nbElements) return false;
  for (int i = 0; i < nbElements; ++i)
    if(elements[i] != autre.elements[i]) return false;
  return true;
}

template<class T>
Tableau<T>& Tableau<T>::operator=(const Tableau<T>& autre) {
  if(this == &autre) //[[likely ou unlikely]]
    return *this;

  if (capacite <= autre.nbElements) {
    capacite = autre.capacite;
    delete[] elements;
    elements = new T[capacite];
  }
  nbElements = autre.nbElements;
  for (int i = 0; i < nbElements; ++i) {
    elements[i] = autre.elements[i];
  }
  return *this;
}

#endif
