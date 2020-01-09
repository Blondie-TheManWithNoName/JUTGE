#include "call_registry.hpp"

call_registry::call_registry() throw(error) {
	_M = 101;
	_quants = 0;
	try
	{
		_taula = new node_hash*[_M];
		for (nat i = 0; i < _M; ++i)
			_taula[i] = NULL;
	}
	catch(error)
	{
		throw error();
	}
}

call_registry::call_registry(const call_registry& R) throw(error) {
	node_hash* n;
	node_hash* aux;
	_taula = new node_hash*[R._M];
	for (nat i = 0; i < R._M; ++i)
	{
		_taula[i] = NULL;
		n = R._taula[i];
		if (n != NULL)
		{
			while (n != NULL)
			{
				try {
					aux = new node_hash;
					aux -> _p = n -> _p;
					aux -> _seg = _taula[i];
					_taula[i] = aux;
					n = n -> _seg;
				}
				catch(error) {
					(*this).~call_registry();
				}
			}
		}
	}

	_M = R._M;
	_quants = R._quants;
}

call_registry& call_registry::operator=(const call_registry& R) throw(error) {
	
	call_registry tmp(R);
	node_hash** aux = _taula;
	_taula = tmp._taula;
	_quants = tmp._quants;
	_M = tmp._M;
	tmp._taula = aux;
	return *this;
}

call_registry::~call_registry() throw() {
	if (_taula != NULL)
	{
		for (nat i = 0; i < _M; ++i) {
			elimina(_taula[i]);
		}
		delete[] _taula;
		_taula = NULL;
		_M = 0;
		_quants = 0;
	}
}

void call_registry::elimina(node_hash* &n) {
	if (n != NULL)
	{
		elimina(n -> _seg);
		delete n;
		n = NULL;
	}
}

void call_registry::registra_trucada(nat num) throw(error) {
	// Redispersio
	if (double(double(_quants)/double(_M)) >= 0.75)
		redispersio();
	
	// Dispersio
	int i = dispersio(num);
	node_hash* n = _taula[i];

	while (n != NULL and num != n -> _p.numero())
		n = n -> _seg;

	if (n != NULL)
		++n -> _p;
	else
	{
		try
		{
			n = new node_hash;
			n -> _seg = _taula[i];
			phone aux(num, "", 1);
			n -> _p = aux;
			_taula[i] = n; 
			++_quants;
		}
		catch (error)
		{
			throw error();
		}
	}
}

void call_registry::assigna_nom(nat num, const string& name) throw(error) {
	// Redispersio
	if (double(double(_quants)/double(_M)) >= 0.75)
		redispersio();
	
	// Dispersio
	int i = dispersio(num);
	node_hash* n = _taula[i];

	while (n != NULL and num != n ->_p.numero())
		n = n -> _seg;

	if (n != NULL)
	{
		phone aux(num, name, n -> _p.frequencia());
		n -> _p = aux;
	}
	else
	{
		try 
		{
			n = new node_hash;
			n -> _seg = _taula[i];
			phone aux(num, name, 0);
			n -> _p = aux;
			_taula[i] = n;
			++_quants;
		}
		catch (error)
		{
			throw error();
		}
	}
}

void call_registry::elimina(nat num) throw(error) {
	// Dispersio
	int i = dispersio(num);
	node_hash* n = _taula[i], *ant = NULL;

	while (n != NULL and num != n ->_p.numero())
	{
		ant = n;
		n = n -> _seg;
	}

	if (n != NULL)
	{
		if (ant == NULL)
			_taula[i] = n -> _seg;
		
		else
			ant -> _seg = n -> _seg;

		delete(n);
		--_quants;
	}
	else
		throw error(ErrNumeroInexistent);
}

bool call_registry::conte(nat num) const throw() {
	// Dispersio
	int i = dispersio(num);
	node_hash* n = _taula[i];
	bool t = false;

	while (n != NULL and num != n ->_p.numero())
		n = n -> _seg;

	if (n != NULL)
		t = true;

	return t;
}

string call_registry::nom(nat num) const throw(error) {
	// Dispersio
	int i = dispersio(num);
	node_hash* n = _taula[i];
	string str;

	while (n != NULL and num != n ->_p.numero())
		n = n -> _seg;

	if (n != NULL)
		str = n -> _p.nom();
	
	else
		throw error(ErrNumeroInexistent);

	return str;
}

nat call_registry::num_trucades(nat num) const throw(error) {
	// Dispersio
	int i = dispersio(num);
	node_hash* n = _taula[i];
	int compt;

	while (n != NULL and num != n ->_p.numero())
		n = n -> _seg;

	if (n != NULL)
		compt = n -> _p.frequencia();
	else
		throw error(ErrNumeroInexistent);

	return compt;	
}

bool call_registry::es_buit() const throw() {
	return !_quants;
}

nat call_registry::num_entrades() const throw() {
	return _quants;
}

void call_registry::dump(vector<phone>& V) const throw(error) {
	node_hash* n;
	V.resize(0);

	// afegint al vector els phones
	for (nat i = 0; i < _M; ++i)
	{
		n = _taula[i];
		while (n != NULL)
		{
			if (n -> _p.nom() != "")
				V.push_back(n -> _p);
			
			n = n -> _seg;
		}
	}

	// comprovació de noms
	for (nat i = 0; i < V.size(); ++i)
	{
		for (nat j = i + 1; j < V.size(); ++j)
		{
			if (V[i].nom() == V[j].nom())
				throw error(ErrNomRepetit);
		}
	}
}
