/*! \file classe.h
	\brief Definição da ClasseEstatica e da ClasseInstancia
*/
#ifndef CLASSE_CLASSE_H
#define CLASSE_CLASSE_H

class ClasseEstatica;
class ClasseInstancia;

#include "classeLeitor.h"
#include <map>
#include <vector>

using namespace std;
class ClasseEstatica {
private:
	map<string, typedElement*> staticFields;
	Leitor *classe;
	static vector<ClasseInstancia*> objetos;

public:
	ClasseEstatica(Leitor*);
	typedElement getField(string);
	bool setField(string, typedElement);
	bool setFinals(string, typedElement);
	ClasseInstancia *getInstance();
	Leitor *getDef();
	static void addObject(ClasseInstancia*);
};


class ClasseInstancia {
private:
	map<string, typedElement*> localFields;
	ClasseEstatica *classe;
	static vector<ClasseInstancia*> objetos;

public:

	ClasseInstancia(ClasseEstatica*);
	ClasseEstatica *getStatic();
	typedElement getField(string);
	bool setField(string, typedElement);
	bool setFinals(string, typedElement);
	static void addObject(ClasseInstancia*);
	void show();
};

#endif