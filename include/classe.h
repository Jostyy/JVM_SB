/*! \file classe.h
	\brief Definição da ClasseEstatica e da ClasseInstancia
*/
#ifndef CLASSE_CLASSE_H
#define CLASSE_CLASSE_H

class ClasseEstatica;
class ClasseInstancia;

#include "classeLeitor.h"
#include "heap.h"
#include <map>

using namespace std;
class ClasseEstatica {
private:
	map<string, typedElement*> staticFields;
	Leitor *classe;

public:
	ClasseEstatica(Leitor*);
	typedElement getField(string);
	bool setField(string, typedElement);
	bool setFinals(string, typedElement);
	ClasseInstancia *getInstance();
	Leitor *getDef();
};


class ClasseInstancia {
private:
	map<string, typedElement*> localFields;
	ClasseEstatica *classe;

public:
	ClasseInstancia(ClasseEstatica*);
	ClasseEstatica *getStatic();
	typedElement getField(string);
	bool setField(string, typedElement);
	bool setFinals(string, typedElement);
	void show();
};

#endif