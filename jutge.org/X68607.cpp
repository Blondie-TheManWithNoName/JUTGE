#include <iostream>
#include <cstddef>
#include <algorithm>
using namespace std;
typedef unsigned int nat;

template <typename Clau>
class dicc {
 
public:
     // Constructora per defecte. Crea un diccionari buit.
    dicc();

    // Les tres grans: Constructora per còpia, destructora, operador d’assignació
    dicc(const dicc &d);
    ~dicc();
    dicc& operator=(const dicc &d);

    // Insereix la clau k en el diccionari. Si ja hi era, no fa res.
    void insereix(const Clau &k);

    // Elimina la clau k del diccionari. Si no hi era, no fa res.
    void elimina(const Clau &k);

    // Consulta si la clau k està en el diccionari.
    bool consulta(const Clau &k) const;

    // Retorna quants elements (claus) té el diccionari.
    nat quants() const;

    // Impressió per cout de claus del diccionari en ordre ascendent, separades per
    // un espai, començant per ’[’ i acabant per ’]’, en dues versions:
    // Imprimeix totes les claus
    void print() const;

    // Imprimeix les claus entre k1 i k2 ambdós incloses. Pre: k1 <= k2
    void print_interval(const Clau &k1, const Clau &k2) const;

    // Retorna la clau més petita i la més gran respectivament.
    // Pre: El diccionari no està buit
    Clau min() const;
    Clau max() const;

    // Retorna la clau de la posició i-èssima (comptant-les en ordre ascendent).
    // Pre: El diccionari no està buit. 1 <= i <= quants()
    Clau iessim(nat i) const;
 
private:

	// Aquí van els atributs i mètodes privats
	struct node {
        Clau _k;
        node* fesq;
        node* fdret;
        node(const Clau &k, node* fesq = NULL, node* fdret = NULL) throw();
    	nat _szn;
    };
    nat _sz;		// elements que conté l'arbre
    node* _arrel;

    //Metodes
    // Funció auxiliar per inserir una clau a l'arbre
    node* insereix_aux(node* n, const Clau k, bool &repeat);
    
    // Funció auxiliar per treure per pantalla l'arbre, en un recorrecut inordre
    void print_aux(node* n, bool &t) const;
    
    // Funció auxiliar per treure per pantalla alguns nodes de l'arbre, en un recorrecut inordre
    void print_interval_aux(node* n, const Clau &k1, const Clau &k2, bool &t) const;
    
    // Retorna el primer element, si llegimen inordre
    // Es a dir, el més petit
    Clau min(node* n) const;
    
    // Retorna el l'últim element, si llegimen inordre
    // Es a dir, el més gran
    Clau max(node* n) const;
    
    // Retorna true si k es troba a l'arbre
    void consulta(node* n, const Clau &k, bool &t) const;
	
    // Retorna la Clau número i, si fem un recoirrecut inordre
	Clau iessim(node* n, nat i, bool &t) const;
	
    // Funció auxiliar per l'operator =
	node* igualar(node* n);
	
    // Funció auxiliar per el destructor
	void esborrar(node* &n);
	
    // Funció auxiliar per la funció pública elimina,
	node* elimina(node* n, const Clau &k, bool &t);
	
    // Funció auxiliar per la funció pública elimina
	node* ajunta(node* n1, node* n2);
	
    // Funció auxiliar per la funció pública elimina
	node* elimina_maxim(node* p);
	

 };
 
 // Aquí va la implementació dels mètodes públics i privats

template <typename Clau>
dicc<Clau>::node::node (const Clau &k, node* esq, node* dret) throw() :_k(k), fesq(esq), fdret(dret) 
{}

template <typename Clau>
dicc<Clau>::dicc()
{
	_arrel = NULL;
	_sz = 0;
}

template <typename Clau>
dicc<Clau>::~dicc()
{
	esborrar(_arrel);

}

template <typename Clau>
dicc<Clau>::dicc(const dicc &d)
{
	*this = d;
}

template <typename Clau>
dicc<Clau>& dicc<Clau>::operator=(const dicc &d)
{
	_sz = d._sz;
	_arrel = igualar(d._arrel);
	return *this; 
}

template <typename Clau>
typename dicc<Clau>::node*
dicc<Clau>::igualar(node* n)
{
	node* n1 = NULL;
	if (n != NULL)
		n1 = new node(n -> _k, igualar(n -> fesq), igualar(n -> fdret));
	return n1;
}

template <typename Clau>
void dicc<Clau>::esborrar(node* &n)
{
	if (n != NULL)
	{
		esborrar(n -> fesq);
		esborrar(n -> fdret);
		delete(n);
	}
}

template <typename Clau>
void dicc<Clau>::insereix(const Clau &k)
{
	bool repeat = false;
    _arrel = insereix_aux(_arrel, k, repeat);

}

template <typename Clau>
typename dicc<Clau>::node*
dicc<Clau>::insereix_aux(node* n, const Clau k, bool & repeat) // 
{
    if (n != NULL)
    {
        if  (k > n -> _k)
        {
            n -> fdret = insereix_aux(n -> fdret, k, repeat);
            if (not repeat)
            	++n -> _szn;
        }
        else if (k < n -> _k)
        {
            n -> fesq = insereix_aux(n -> fesq, k, repeat);
            if (not repeat)
        		++n -> _szn;
    	}
    	else
    		repeat = true;
    }
    else
    {
    	n = new node(k, NULL, NULL);
    	n -> _szn = 1;
    	++_sz;
    }

    return n;
}

template <typename Clau>
void dicc<Clau>::print() const
{
	cout << "[";
	bool t = false;
	print_aux(_arrel, t);
	cout << "]";
}

template <typename Clau>
void dicc<Clau>::print_aux(node* n, bool &t) const
{
	if ( n != NULL)
	{
		print_aux(n -> fesq, t);
		if (!t)
		{
			cout << n -> _k;
			t = true;
		}
		else
			cout << " " << n -> _k;
//		cout << " szn:" << n -> _szn;			// debug
		print_aux(n -> fdret, t);

	}
}

template <typename Clau>
void dicc<Clau>::print_interval(const Clau &k1, const Clau &k2) const
{
	cout << "[";
	bool t = false;
	print_interval_aux(_arrel, k1, k2, t);
	cout << "]";
}	

template <typename Clau>
void dicc<Clau>::print_interval_aux(node* n, const Clau &k1, const Clau &k2, bool &t) const
{
	if ( n != NULL)
	{
		if (n -> _k >= k1)
			print_interval_aux(n -> fesq, k1, k2, t);

		if (n -> _k >= k1 and n -> _k <= k2)
		{
			if (!t)
			{
				cout << n -> _k;
				t = true;
			}
			else
				cout << " " << n -> _k;
		}
		if (n -> _k <= k2)
			print_interval_aux(n -> fdret, k1, k2, t);
	}
}

template <typename Clau>
nat dicc<Clau>::quants() const 
{
	return _sz;
}

template <typename Clau>
Clau dicc<Clau>::min() const 
{
	return min(_arrel);
}


template <typename Clau>
Clau dicc<Clau>::min(node* n) const
{
	Clau res;
	if (n -> fesq != NULL)
	{
		res = min(n -> fesq);
	}
	else
		res = n -> _k;
	return res;
}


template <typename Clau>
Clau dicc<Clau>::max() const
{
	return max(_arrel);
}

template <typename Clau>
Clau dicc<Clau>::max(node* n) const
{
	Clau res;
	if (n -> fdret != NULL)
	{
		res = max(n -> fdret);
	}
	else
		res = n -> _k;
	return res;
}

template <typename Clau>
bool dicc<Clau>::consulta(const Clau &k) const
{
	bool t = false;
	consulta(_arrel, k, t);

	return t;
}


template <typename Clau>
void dicc<Clau>::consulta(node* n, const Clau &k, bool &t) const
{
	if (n != NULL and !t)
	{
		if (n -> _k == k)
			t = true;
		else
		{
			if (k > n -> _k)
				consulta(n -> fdret, k, t);
			else
				consulta(n -> fesq, k, t);
		}
	}
}


template <typename Clau>
Clau dicc<Clau>::iessim(nat i) const
{
	bool t = false;
	return iessim(_arrel, i, t);
}


template <typename Clau>
Clau dicc<Clau>::iessim(node* n, nat i, bool &t) const
{
	Clau res;
	if (n != NULL and i > 0)
	{
		if (n -> fesq != NULL)
		{
//			cout << "n -> fesq: " << n -> fesq -> _k << endl;
//			cout << "n -> fesq -> _szn: " << n -> fesq -> _szn << endl;
			if (n -> fesq -> _szn + 1 > i)
			{
				res = iessim(n -> fesq, i, t);
			}
			else if (n -> fesq -> _szn + 1 < i)
				res = iessim(n -> fdret, i - n -> fesq -> _szn - 1, t);
			else
				res = n -> _k;
		}
		else
		{
			if (n -> fdret != NULL)
			{
			}
			if (i > 1)
				res = iessim(n -> fdret, i - 1, t);
			else
				res = n -> _k;
		}

	}
	return res;
}	


template <typename Clau>
void dicc<Clau>::elimina(const Clau &k)
{
	bool t = false;
	_arrel = elimina(_arrel, k, t);
}

template <typename Clau>
typename dicc<Clau>::node*
dicc<Clau>::elimina(node* n, const Clau &k, bool &t)
{
	node* p = n;
	if (n != NULL)
	{
		if (k < n -> _k)
		{
			n -> fesq = elimina(n -> fesq, k, t);
			if (t)
				-- n -> _szn;
		}
		else if (k > n -> _k)
		{
			n -> fdret = elimina(n -> fdret, k, t);
			if (t)
				-- n -> _szn;
		}
		else
		{
			t = true;
			n = ajunta(n -> fesq, n -> fdret);
			--_sz;
			delete(p);
		}
	}

	return n;
}


template <typename Clau>
typename dicc<Clau>::node*
dicc<Clau>::ajunta(node* n1, node* n2)
{
	if (n1 == NULL)
	{
		return n2;
	}
	if (n2 == NULL)
	{
		return n1;
	}
	node* p = elimina_maxim(n1);
	p -> fdret = n2;
//	cout << "n2 sz: " << n2 -> _szn;
//	cout << "p sz: " << p -> _szn;
	p -> _szn += n2 -> _szn + 1; 

	return p;
}


template <typename Clau>
typename dicc<Clau>::node*
dicc<Clau>::elimina_maxim(node* p)
{
	node* p_orig = p;
	node* pare = NULL;
	while (p -> fdret != NULL)
	{
		pare = p;
		--p -> _szn;
		p = p -> fdret;
	}
	if (pare != NULL)
	{
		pare -> fdret = p -> fesq;
		p -> fesq = p_orig;
		p -> _szn =  p_orig -> _szn;
	}

	return p;
}

/*
123 1234 234 214 4234 325345 6345 345 345 3425 46 45 4 54 54 6 346 7 33736 56 546 36 57 456 563 465 65 754 6 56  567 546 35 6 754 636 5 786 75 652 45 45 7 456 7 4567 5 6 242 5626 5 63565 654 6



123 1234 234 214 4234 325345 6345 345 345 3425 46 45 4 54 54 6 346 7

*/
