#include "phone.hpp"
#include <iostream>

/* Construeix un telèfon a partir del seu número (num), el seu nom
(name) i el seu comptador de trucades (compt). 
Es produeix un error si name no és un identificador legal. */
phone::phone(nat num, const string& name, nat compt) throw(error)
{
	for (unsigned int i = 0; i < name.size(); ++i)
	{
		if (name[i] == DELETECHAR or name[i] == ENDCHAR)
			throw error(ErrNomIncorrecte);
	}
	_num = num;
	_nom = name;
	_freq = compt;
}

/* Tres grans. Constructor per còpia, operador d'assignació i destructor. */				
phone::phone(const phone& T) throw(error)
{
  	*this = T;
}

phone& phone::operator=(const phone& T) throw(error)
{
 	_num = T._num;
	_nom = T._nom;
	_freq = T._freq;
	return *this;
}

phone::~phone() throw(){}

/* Retorna el número de telèfon. */
nat phone::numero() const throw()
{
	return _num;
}

/* Retorna el nom associat al telèfon, eventualment l'string buit. */
string phone::nom() const throw()
{
	return _nom;
}

/* Retorna el número de vegades que s'ha trucat al telèfon. */
nat phone::frequencia() const throw()
{
	return _freq;
}

/* Operador de preincrement. 
Incrementa en 1 el número de vegades que s'ha trucat al telèfon i
retorna una referència a aquest telèfon. */
phone& phone::operator++() throw()
{
	++_freq;
	return *this;
}

/* Operador de postincrement. 
Incrementa en 1 el número de vegades que s'ha trucat al telèfon i
retorna una còpia d'aquest telèfon sense incrementar. */
phone phone::operator++(int) throw() 
{
  	phone aux(_num, _nom, _freq);
	++_freq;
  	
	return aux;
}

/* Operadors de comparació.  L'operador > retorna cert, si i només si, el
telèfon sobre el que s'aplica el mètode és més freqüent que el
telèfon T, o a igual freqüència, el nom associat al telèfon és
major en ordre lexicogràfic que el nom associat a T. 
La resta d'operadors es defineixen consistentment respecte a >. */
bool phone::operator==(const phone& T) const throw()
{
  	bool b = true;
	if (_nom != T._nom) b = false;
	if (_freq != T._freq) b = false;
  	return b;
}

bool phone::operator!=(const phone& T) const throw()
{
  	return !(*this == T);
}

bool phone::operator<(const phone& T) const throw() // FIX
{
    bool b = true;
	if (_freq > T._freq) b = false;
	if (_nom >= T._nom and _freq == T._freq) b = false;
   	return b;
}

bool phone::operator>(const phone& T) const throw() // FI
{
    bool b = true;
	if (_freq < T._freq) b = false;
	if (_nom <= T._nom and _freq == T._freq) b = false;
  	return b;
}

bool phone::operator<=(const phone& T) const throw()
{
  	return !(*this > T);
}

bool phone::operator>=(const phone& T) const throw()
{
  	return !(*this < T);
}
