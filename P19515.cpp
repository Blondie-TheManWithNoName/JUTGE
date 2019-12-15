#include <iostream>
#include<algorithm>
#include <cstddef>
using namespace std;


typedef unsigned int nat;

template <typename T>
class Arbre {
private:
  Arbre(): _arrel(NULL) {};
  struct node {
    T info;
    node* primf;
    node* seggerm;
    node* ult;
    nat _elem;    // nombre d'elements
    nat _h;    // altura del subarbre
  };
  node* _arrel;
  static node* copia_arbre(node* p);
  static void destrueix_arbre(node* p) throw(); 
  double subarbres(node* n, double &max) const;
  void  calcular_h(node* &n);


public:
  // Construeix un Arbre format per un únic node que conté a x.
  Arbre(const T &x);

  // Tres grans.
  Arbre(const Arbre<T> &a);
  Arbre& operator=(const Arbre<T> &a);
  ~Arbre() throw();
  void print(node* n);

  // Col·loca l'Arbre donat com a primer fill de l'arrel de l'arbre sobre el que s'aplica el mètode i l'arbre a queda invalidat; després de fer b.afegir_fill(a), a no és un arbre vàlid.
  void afegir_fill(Arbre<T> &a);


  void nivell(nat i) const;
  void nivell(node* n, nat i) const;

    int alcada();
    void alcada(node* n, int &x);

    int elem();
    int elem(node* n);

    double subarbres() const;

    void print();


  // Iterador sobre arbre general.
  friend class iterador;
  class iterador {
  public:
    friend class Arbre;

    // Construeix un iterador no vàlid.
    iterador() throw();

    // Retorna el subarbre al que apunta l'iterador; llança un error si l'iterador no és vàlid.
    Arbre<T> arbre() const;

    // Retorna l'element del node al que apunta l'iterador o llança un error si l'iterador no és vàlid.
    T operator*() const;

    // Retornaiterador un iterador al primogenit del node al que apunta; llança un error si l'iterador no és vàlid.
  iterador primogenit() const;

    // Retorna un iterador al següent germà del node al que apunta; llança un error si l'iterador no és vàlid.
    iterador seg_germa() const;

    // Operadors de comparació.
    bool operator==(const iterador &it) const {
      return _p == it._p;
    };
    bool operator!=(const iterador &it) const {
      return _p != it._p;
    };
    static const int IteradorInvalid = 410;

  private:
    Arbre<T>::node* _p;
  };
    
  // Retorna un iterador al node arrel de l'Arbre (un iterador no vàlid si l'arbre no és vàlid).
  iterador arrel() const throw();

  // Retorna un iterador no vàlid.
  iterador final() const throw();

  static const int ArbreInvalid = 400;
};
// La còpia es fa seguint un recorregut en preordre.
template <typename T>				
typename Arbre<T>::node* Arbre<T>::copia_arbre(node* p) { 
  node* aux = NULL;
  if (p != NULL) {
    aux = new node;
    try {
      aux -> info = p -> info;
      aux -> _elem = p -> _elem;
      aux -> _h = p -> _h;
      aux -> primf = aux -> seggerm = NULL;
      aux -> primf = aux -> ult = NULL;
      aux -> primf = copia_arbre(p -> primf);
      aux -> seggerm = copia_arbre(p -> seggerm);
    }
    catch (...) {
      destrueix_arbre(aux);
    }
  }
  return aux;
}

// La destrucció es fa seguint un recorregut en postordre.
template <typename T>	
void Arbre<T>::destrueix_arbre(node* p) throw() { 
  if (p != NULL) {
    destrueix_arbre(p -> primf);
    destrueix_arbre(p -> seggerm);
    delete p;
  }
}

// Construcció d'un arbre que conté un sol element x a l'arrel.
template <typename T>	
Arbre<T>::Arbre(const T &x) {
  _arrel = new node; 
  try {
    _arrel -> info = x;
    _arrel -> _elem = 1;
    _arrel -> _h = 1;
    _arrel -> seggerm = NULL;
    _arrel -> primf = NULL;
  } 
  catch (...) {
    delete _arrel;
    throw;
  }
}

template <typename T>	
Arbre<T>::Arbre(const Arbre<T> &a) { 
  _arrel = copia_arbre(a._arrel);
}


template <typename T>
int Arbre<T>::alcada() {
  int x = 0;
  alcada(_arrel, x);
  return x + 1;
}


template <typename T>
void Arbre<T>::alcada(node* n, int &x)  {

  if (n != NULL)
  {
    if (n -> primf != NULL)
      alcada(n -> primf, ++x);
    alcada(n -> seggerm, x);
  } 
}

template <typename T>
int Arbre<T>::elem() {
  _arrel -> seggerm = NULL;
  return elem(_arrel);
}

template <typename T>
int Arbre<T>::elem(node* n) {
  int res = 0;
  if (n != NULL)
    res =  elem(n -> primf) + elem(n -> seggerm) + 1; 
  else
    res = 0;
  return res;
}

template <typename T>
void Arbre<T>::nivell(nat i) const{
  nivell(_arrel, i);
}

template <typename T>
void Arbre<T>::nivell(node* n, nat i) const {
  
  if (n != NULL)
  {
    if (i == 0)
    {
      cout << " " << n -> info;
      nivell(n -> seggerm, i);
    }
    else
    {
      nivell(n -> primf, i - 1);
      nivell(n -> seggerm, i);
      
    }
  }
}

template <typename T>	
Arbre<T>&  Arbre<T>::operator=(const Arbre<T> &a) { 
  Arbre<T> tmp(a);
  node* aux = _arrel;
  _arrel = tmp._arrel;
  tmp._arrel = aux;
  return *this;
}

template <typename T>	
Arbre<T>::~Arbre() throw() { 
  destrueix_arbre(_arrel);
}

template <typename T>
void  Arbre<T>::calcular_h(node* &n)
{
  if (n -> primf != NULL and n -> primf -> seggerm != NULL)
  {
    //cout << "1" << endl;
    nat max = 0;
    node* aux = n -> primf;
    while (aux != NULL)
    {
      if (aux -> _h > max)
        max = aux -> _h;
      aux = aux -> seggerm;
    }
    n -> _h = max + 1;
  }
  else if (n -> primf == NULL)
    n -> _h = 1;
  else if (n -> primf != NULL and n -> primf -> seggerm == NULL)
    n -> _h = n -> primf -> _h + 1;

}



template <typename T> 
void Arbre<T>::afegir_fill(Arbre<T> &a) { 
  if (_arrel == NULL or a._arrel == NULL) {
    throw ArbreInvalid;
  }

  //a._arrel -> seggerm = _arrel -> primf;
  //_arrel -> primf = a._arrel;
  //cout << "_arrel: " << _arrel -> info << endl;
  //cout << "_arrel -> elem: " << _arrel -> _elem << endl;
  _arrel -> _elem += a._arrel -> _elem;
  //_arrel -> info = 90;
  if (_arrel -> primf == NULL)
  {
    _arrel -> primf = a._arrel;
    _arrel -> ult = _arrel -> primf;
  //cout << "_arrel -> h: " << _arrel -> _h << endl;
    //_arrel -> _h += a._arrel -> _h + 1;

  }
  else
  {
    node* aux = _arrel;
    // _arrel->primf;
    //while (aux->seggerm != NULL)
      //aux = aux->seggerm;
    aux -> ult-> seggerm = a._arrel;
    aux -> ult = aux -> ult -> seggerm;
  }
  calcular_h(_arrel);
  //cout << "_arrel2: " << _arrel -> info << endl;
  //cout << "_arrel -> elem2: " << _arrel -> _elem << endl;
  a._arrel = NULL;
}

template <typename T>
typename Arbre<T>::iterador Arbre<T>::arrel() const throw() { 
  iterador it;
  it._p = _arrel;
  return it;
}

template <typename T> 
typename Arbre<T>::iterador Arbre<T>::final() const throw() { 
  return iterador();
}

template <typename T>       
Arbre<T>::iterador::iterador() throw(): _p(NULL) { 
}

template <typename T> 
T Arbre<T>::iterador::operator*() const { 
  if (_p == NULL) {
    throw IteradorInvalid;
  }
  return _p -> info;
}

template <typename T> 
typename Arbre<T>::iterador Arbre<T>::iterador::primogenit() const { 
  if (_p == NULL) {
    throw IteradorInvalid;
  }
  iterador it;
  it._p = _p -> primf;
  return it;
}

template <typename T> 
typename Arbre<T>::iterador Arbre<T>::iterador::seg_germa() const { 
  if (_p == NULL) {
    throw IteradorInvalid;
  }
  iterador it;
  it._p = _p -> seggerm;
  return it;
}

template <typename T> 
Arbre<T> Arbre<T>::iterador::arbre() const { 
  if (_p == NULL) {
    throw IteradorInvalid;
  }
  Arbre<T> a;
  a._arrel = _p;
  Arbre<T> aux(a);
  a._arrel = NULL;
  return aux;
}

template <typename T> 
double Arbre<T>::subarbres() const{
  double max = 0;
  return subarbres(_arrel, max);
}

template <typename T> 
double Arbre<T>::subarbres(node* n, double &max) const {
	if (n != NULL) {
		if (max <  double(double(n -> _elem) / double(n -> _h)))
			max = double(double(n -> _elem) / double(n -> _h));
		subarbres(n -> primf, max);
		subarbres(n -> seggerm, max);
	}
	return max;
}



template <typename T>
void Arbre<T>::print()
{
  print(_arrel);
  cout << endl;
}

template <typename T>
void Arbre<T>::print(node* n)
{
  if (n != NULL)
  {
    cout << " " << n -> info;
   //cout << " e" << n -> _elem;
    //cout << " h" << n -> _h;
    print(n -> primf);
    print(n -> seggerm);
  }
}

#include <iomanip>
#include <stdio.h>

void subarbres(Arbre<int> a) {
      printf ("%.3f\n", a.subarbres());
}


Arbre<int> crear_arbre()
{
  nat n;
  cin >> n;
  Arbre <int> a(0);
  for (nat i = 0; i < n; ++i)
  {
    Arbre <int> b(0);
    b = crear_arbre();
    a.afegir_fill(b);
  }

  return a;

}


int main() {
  nat n;
  cin >> n;
  for (nat i = 0; i < n; ++i)
  {
    Arbre <int> a(0);
    a = crear_arbre();
    subarbres(a);    
  }
} 

