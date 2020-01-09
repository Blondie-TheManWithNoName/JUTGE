#include "easy_dial.hpp"

easy_dial::easy_dial(const call_registry& R) throw(error) {
	
	// Inicialitzem
	_arrel = NULL;
	totFreq = 0;
	pre.act = phone::ENDPREF;
	pre.hist = "";
	pre.indef = true;
	pre.punterNULL = false;
	vector<phone> v;
	R.dump(v);
	v_mitj.resize(v.size());

	// Ordenar v segons la freqencia
	ordenar(v);

	// Anar inserint v[i] al trie
	string s;
    for (unsigned int i = 0; i < v.size(); ++i)
    {
    	v_mitj[i] = v[i].frequencia();
    	totFreq += v[i].frequencia();
    	if (i == 0) s = phone::ENDPREF + v[i].nom();
    	else s = v[i].nom();
    	bool ins = false;
    	if (i == 0)
    		_arrel = insereix(_arrel, 0, s, v[i], ins);
    	else
    		_arrel -> _cen = insereix(_arrel -> _cen, 0, s, v[i], ins);

    }
	actTrie = _arrel;
}

easy_dial::easy_dial(const easy_dial& D) throw(error) {
	_arrel = copia(D._arrel, NULL);
	actTrie = _arrel;
	totFreq = D.totFreq;
	v_mitj = D.v_mitj;
	pre = D.pre;
}

typename easy_dial::node_tst* easy_dial::copia(node_tst* n, node_tst* ant) throw() {
	node_tst* res = NULL;
	if (n != NULL)
	{
		try
		{
			res = new node_tst;
			res -> _v = n -> _v;
			res -> _c = n -> _c;
			res -> _ant = ant;
			res -> p_indef = n -> p_indef;
			res -> _cen = copia(n -> _cen, res);
			res -> _esq = copia(n -> _esq, res -> _ant);
			res -> _dret = copia(n -> _dret, res -> _ant);
		}
		catch (error e)
		{
			esborrar(res);
		}
	}

	return res;
}

easy_dial&  easy_dial::operator=(const easy_dial& D) throw(error) {
	easy_dial tmp(D);
	node_tst* aux = _arrel; // aux per evitar cridar al destructor
	actTrie = _arrel;
	totFreq = D.totFreq;
	v_mitj = D.v_mitj;
	pre = D.pre;
	_arrel = tmp._arrel;
	tmp._arrel = aux;
	return *this;
}

easy_dial::~easy_dial() throw() {
	esborrar(_arrel);
	actTrie = _arrel;
	vector<double>().swap(v_mitj);	// esborrem el vector
}								    // si no ho feiem sortia un error
									// free() double free detected in tcache 2
void easy_dial::esborrar(node_tst* &n) {
	if (n != NULL)
	{
		esborrar(n -> _esq);
		esborrar(n -> _dret);		
		esborrar(n -> _cen);
		delete(n);
		n = NULL;
	}
}


string easy_dial::inici() throw(){
	pre.act = phone::ENDPREF;
	pre.hist = "";
	pre.indef = false;
	pre.punterNULL = false;
	actTrie = _arrel;
	if (_arrel != NULL)
	{
		return _arrel -> _v.nom();
	}
	return "";
	
}

string easy_dial::seguent(char c) throw(error) {

	if (pre.indef != true) 
	{
		if (actTrie != NULL and not pre.punterNULL)
		{
			node_tst* aux = NULL;
			pre.act = c;
			pre.hist += c;
			aux = busca(actTrie -> _cen, c);
			if (aux != NULL and not aux -> p_indef)
			{
				actTrie = aux;
				return actTrie -> _v.nom();
			}
			else
			{
				pre.punterNULL = true;
				return "";
			}
		}
		else
		{
			pre.indef = true;
			throw error(ErrPrefixIndef);
		}
	}
	else
		throw error(ErrPrefixIndef);
}

string easy_dial::anterior() throw(error) {
	
	if (pre.indef != true)
	{
		if (pre.hist.size() > 0)
		{
			pre.hist.resize(pre.hist.size() - 1);
			pre.act = pre.hist[pre.hist.size() - 1];
		}
		else
			pre.indef = true;
		if (_arrel != NULL and actTrie != NULL)
		{
			if (actTrie -> _ant != NULL and not pre.punterNULL)
			{
				actTrie = actTrie -> _ant;
				return actTrie -> _v.nom();
			}
			else
			{
				if (pre.punterNULL)
				{
					pre.punterNULL = false;
					return actTrie -> _v.nom();
				}
				throw error(ErrNoHiHaAnterior);
			}
		}
		else
			throw error(ErrNoHiHaAnterior);
	}
	else
		throw error(ErrPrefixIndef);
}

nat easy_dial::num_telf() const throw(error) {

	if (pre.indef != true)
	{
		if (actTrie != NULL and not pre.punterNULL)
		{
			return actTrie -> _v.numero();
		}
		else
			throw error(ErrNoExisteixTelefon);
	}
	else
		throw error(ErrPrefixIndef);
}

void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error) {
	node_tst* n = _arrel;

	for (nat i = 0; i < pref.size() and n != NULL; ++i)	
	{
		if (n != NULL)
			n = n -> _cen;

		n = busca(n, pref[i]);
	}
	if (n != NULL)
		noms(n -> _cen, result);
}

double easy_dial::longitud_mitjana() const throw() {

	double suma = 0;
	for (nat i = 0; i != v_mitj.size(); ++i)
		suma += double(double(double(v_mitj[i])/double(totFreq)) * i);

	return suma;	
}


vector<phone> easy_dial::partir(vector<phone> &v, nat m) {
	vector<phone> v2(v.size() - m);

	for (nat i = 0; i < v2.size(); ++i)    
		v2[i] = v[m + i];  

	v.resize(m);  
	return v2;
}

vector<phone> easy_dial::fusionar(vector<phone> v1, vector<phone> v2) {
  unsigned int c1 = 0, c2 = 0;
  vector<phone> v(v1.size() + v2.size());

  for (unsigned int i = 0; i < v.size(); ++i)
  {
    if (c1 >= v1.size() and c2 < v2.size())
    {
      v[i] = v2[c2];
      ++c2; 
    }
    else if (c2 >= v2.size() and c1 < v1.size())
    {
      v[i] = v1[c1];
      ++c1; 
    }
    else if (v1[c1].frequencia() > v2[c2].frequencia() and c1 < v1.size())
    {
      v[i] = v1[c1];
      ++c1;
    }
    else if (v1[c1].frequencia() < v2[c2].frequencia() and c2 < v2.size())
    {
      v[i] = v2[c2];
      ++c2; 
    }
  }  
  return v;
}

void easy_dial::ordenar(vector<phone>& v) {
	if (v.size() > 1) {    
		nat m = v.size() / 2; 
		vector<phone> v2 = partir(v, m); 
		ordenar(v);    
		ordenar(v2);
		v = fusionar(v, v2);  
	}
}


typename easy_dial::node_tst* easy_dial::insereix(node_tst* n, nat i, const string s, const phone p, bool &inserit) {

	if (n != NULL)
	{
		if (n -> _c > s[i])
		{
			n -> _esq = insereix(n -> _esq, i, s, p, inserit);
			n -> _esq -> _ant = n -> _ant;
		}
		else if (n -> _c < s[i])
		{
			n -> _dret = insereix(n -> _dret, i, s, p, inserit);
			n -> _dret -> _ant = n -> _ant;
		}
		else
		{
			if (n -> p_indef == true and not inserit)	// posem el phone al primer caracter
			{											// on encara no s'ha posat cap
				inserit = true;
				n -> p_indef = false;
				n -> _v = p;
			}
			n -> _cen = insereix(n -> _cen, i + 1, s, p, inserit);
			n -> _cen -> _ant = n;
		}
	}
	else
	{
 		n = new node_tst;
		n -> _esq = n -> _dret = n -> _cen = n -> _ant = NULL;
		n -> p_indef = true;
		n -> _c = s[i];
		if (not inserit)		// posem el phone al caracter
		{
			n -> p_indef = false;
			n -> _v = p;
		}
		if (i < s.size())		// afegim el nom sencer
		{
			inserit = true;
			n -> _cen = insereix(n -> _cen, i + 1, s, p, inserit);
			n -> _cen -> _ant = n;
		}
		else				// posem el phone al final del nom
		{
			n -> _v = p;
		}
	}

	return n;
}

typename easy_dial::node_tst* easy_dial::busca(node_tst* n, const char c) const {
	node_tst* res = NULL;
	if (n != NULL)
	{
		if (n -> _c > c)
			res = busca(n -> _esq, c);
		else if (n -> _c < c)
			res = busca(n -> _dret, c);
		else
			res = n;
	}

	return res;
}

void easy_dial::noms(node_tst* n, vector<string> &v) const {
	string s;
	if (n != NULL)
	{	//distinguim de si es tracta de caracter final (\0), però també
		// de es al final del nom, per què el carcater \0 també es troba
		// a l'arrel del tst
		if (n -> _c == phone::ENDPREF and n -> _ant != NULL)
			v.push_back(n -> _v.nom());
		
		noms(n -> _esq, v);
		noms(n -> _cen, v);
		noms(n -> _dret, v);
	}
}
