#include <iostream>
#include <cstddef>
using namespace std;

template <typename T>
class Abin {
  private:
    struct node {
      node* f_esq;
      node* f_dret;
      T info;
    };
    node* _arrel;
    static node* copia_nodes(node* m);
    static void esborra_nodes(node* m);

  public:
    //constructors
    Abin(): _arrel(NULL) {};
    /* Pre: cert */
    /* Post: el resultat és un arbre sense cap element */
    Abin(Abin<T> &ae, const T &x, Abin<T> &ad);
    /* Pre: cert */
    /* Post: el resultat és un arbre amb un element i dos subarbres */

    // Les tres grans
    Abin(const Abin<T> &a);
    ~Abin();
    Abin<T>& operator=(const Abin<T>& a);

    //ostream& operator<<(ostream &os, const Abin<T> &x);
    // Iterador sobre arbres binaris.
    friend class iterador;
    class iterador {
      private:
        Abin<T>::node* _p;

      public:
        friend class Abin;
        iterador(): _p(NULL) {};
        /* Pre: cert */
        /* Post: Construeix un iterador no vàlid. */

        Abin<T> arbre() const;
        /* Pre: cert */
        /* Post: Retorna el subarbre al que apunta l'iterador; llança un error
        si l'iterador no és vàlid. */

        T operator*() const;
        /* Pre: cert */
        /* Post: Retorna l'element en el node al que apunta l'iterador, o
        llança un error si l'iterador no és vàlid. */


        iterador fesq() const;
        /* Pre: cert */
        /* Post: Retorna un iterador al fill esquerre; llança
        un error si l'iterador no és vàlid. */

        iterador fdret() const;
        /* Pre: cert */
        /* Post: Retorna un iterador al fill dret; llança
        un error si l'iterador no és vàlid. */

        /* Operadors de comparació. */
        bool operator==(const iterador &it) const {
          return _p == it._p;
        };
        bool operator!=(const iterador &it) const {
          return _p != it._p;
        };
        static const int IteradorInvalid = 410;
    };

    //consultors
    bool es_buit() const;
    /* Pre: cert */
    /* Post: el resultat indica si el p.i. és buit o no */

    iterador arrel() const;
    /* Pre: cert */
    /* Post: Retorna un iterador al node arrel. */
    
    iterador final() const;
    /* Pre: cert */
    /* Post: Retorna un iterador no vàlid. */

    int alcada();
    int alcada(node *n);
};


template <typename T>
typename Abin<T>::node* Abin<T>::copia_nodes(node* m) {
/* Pre: cert */
/* Post: si m és NULL, el resultat és NULL; sinó,
   el resultat apunta al primer node d'un arbre binari
   de nodes que són còpia de l'arbre apuntat per m */
  node* n;
  if (m == NULL) n = NULL;
  else {
    n = new node;
    try {   
      n->info = m->info;
      n->f_esq = copia_nodes(m->f_esq);
      n->f_dret = copia_nodes(m->f_dret);
    } catch(...) {
      delete n;
      throw;
    }
  }
  return n;
};

template <typename T>
void Abin<T>::esborra_nodes(node* m) {
/* Pre: cert */
/* Post: no fa res si m és NULL, sinó allibera
   espai dels nodes de l'arbre binari apuntat per m */
  if (m != NULL) {
    esborra_nodes(m->f_esq);
    esborra_nodes(m->f_dret);
    delete m;
  }
};

template <typename T>
Abin<T>::Abin(Abin<T>& ae, const T& x, Abin<T>& ad) {
/* Pre: cert */
/* Post: el resultat és un arbre amb x com arrel, ae com a fill
esquerre i ad com a fill dret. No fa còpia dels arbres ae i ad */
  _arrel = new node;
  try {
    _arrel->info = x;
  }
  catch (...) {
    delete _arrel;
    throw;
  }
  _arrel->f_esq = ae._arrel;
  ae._arrel = NULL;
  _arrel->f_dret = ad._arrel;
  ad._arrel = NULL;
}

template <typename T>
Abin<T>::Abin(const Abin<T> &a) {
  _arrel = copia_nodes(a._arrel);
};

template <typename T>
Abin<T>::~Abin() {
  esborra_nodes(_arrel);
};

template <typename T>
Abin<T>& Abin<T>::operator=(const Abin<T>& a) {
  if (this != &a) {
    node* aux;
    aux = copia_nodes(a._arrel);
    esborra_nodes(_arrel);
    _arrel = aux;
  }
  return (*this);
};

template <typename T>
bool Abin<T>::es_buit() const {
/* Pre: cert */
/* Post: el resultat indica si el p.i. és buit o no */
  return (_arrel == NULL);
};

template <typename T>
typename Abin<T>::iterador Abin<T>::arrel() const {
/* Pre: cert */
/* Post: Retorna un iterador al node arrel. */
  iterador it;
  it._p = _arrel;
  return it;
};

template <typename T>
typename Abin<T>::iterador Abin<T>::final() const{
/* Pre: cert */
/* Post: Retorna un iterador no vàlid. */
  return iterador();
};

template <typename T>
Abin<T> Abin<T>::iterador::arbre() const {
/* Pre: cert */
/* Post: Retorna el subarbre al que apunta l'iterador; llança un error
si l'iterador no és vàlid. */
  if (_p == NULL)
  {
    throw IteradorInvalid;
  }
  Abin<T> a;
  a._arrel = copia_nodes(_p);;
  return a;
};

template <typename T>
T Abin<T>::iterador::operator*() const {
/* Pre: cert */
/* Post: Retorna l'element en el node al que apunta l'iterador, o
llança un error si l'iterador no és vàlid. */
  if (_p == NULL)
    throw IteradorInvalid;
  return _p->info;
};

template <typename T>
typename Abin<T>::iterador Abin<T>::iterador::fesq() const {
/* Pre: cert */
/* Post: Retorna un iterador al fill esquerre; llança
un error si l'iterador no és vàlid. */
  if (_p == NULL) 
  {
    throw IteradorInvalid;
  }
  iterador it;
  it._p = _p->f_esq;
  return it;
};

template <typename T>
typename Abin<T>::iterador Abin<T>::iterador::fdret() const {
/* Pre: cert */
/* Post: Retorna un iterador al fill dret; llança
un error si l'iterador no és vàlid. */
  if (_p == NULL)
    throw IteradorInvalid;
  iterador it;
  it._p = _p->f_dret;
  return it;
};

/*
template <typename T>
int Abin<T>::alcada(node* n)  {
  int res;
  if (n == NULL)
    res = 0;
  else
    res = max(alcada(n->f_esq), alcada(n->f_dret) + 1);
  
  return res;
};

template <typename T>
int Abin<T>::alcada() {
  return alcada(_arrel);

};
*/


//string dep=""; 
//template <typename T>
//ostream& Abin<T>::operator<<(ostream &os, const Abin<T> &x) 
/* Pre: cert */
/* Post: s'han escrit al canal estandard de sortida els elements de x */  
/*{
  string d1=dep;
  if (x.es_buit()) 
    os<<".";
  else {
    os<< "["<<x.arrel()<<"]\n"<<d1<<" \\__";
    dep = d1+" |  ";
    os<< x.fdret();
    os<<"\n"<<d1<<" \\__";
    dep = d1+"    ";
    os<< x.fesq();
  }
  dep=d1;
  return os;
};

*/

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

Abin <int> crear_arbre (vector<int> v,unsigned int n, unsigned int &i)
{
	Abin <int> fe;
	Abin <int> fd;
	Abin <int> a;
	if (i < v.size())
	{
		++i;
		if (v[i] != -1 and i < v.size())
			fe = crear_arbre(v, i, i);
		++i;
		if (v[i] != -1 and i < v.size())
			fd = crear_arbre(v, i, i);
		Abin <int> a1(fe, v[n], fd);
		if (v[n] != -1)
			a = a1;
		}
	return a;
}

void escriure_pre(Abin <int> a)
{
	cout << *(a.arrel()) << " ";
	if (not a.es_buit())
	{
		Abin <int>::iterador it = a.arrel().fesq();
		if (it != a.final())
			escriure_pre(it.arbre());
		it = a.arrel().fdret();
		if (it != a.final())
			escriure_pre(it.arbre());
	}
}

void escriure_post(Abin <int> a)
{
	if (not a.es_buit())
	{
		Abin <int>::iterador it = a.arrel().fesq();
		if (it != a.final())
			escriure_post(it.arbre());
		it = a.arrel().fdret();
		if (it != a.final())
			escriure_post(it.arbre());
	cout << " " << *(a.arrel());
	}
}

void escriure_in(Abin <int> a)
{
	if (not a.es_buit())
	{
		Abin <int>::iterador itf = a.arrel().fesq();
		Abin <int>::iterador itd = a.arrel().fdret();
		if (itf == a.final())
		{
			cout << " " << *(a.arrel());
			if (itd != a.final())
				escriure_in(itd.arbre());
		}
		else
		{
			escriure_in(itf.arbre());
			cout << " " << *(a.arrel());
			if (itd != a.final())
				escriure_in(itd.arbre());
		}
	}
}

int main() {

	string str;
	int n;
	while (getline(cin, str))
	{
	    istringstream ss(str);
		vector <int> v;	    
		while (ss >> n)
			v.push_back(n);
		unsigned int i = 0, n = 0;
		Abin <int> a  = crear_arbre(v, n, i);
		cout << "pos:";
		escriure_post(a);
		cout << endl;
		cout << "ino:";
		escriure_in(a);
		cout << endl;
	}
}