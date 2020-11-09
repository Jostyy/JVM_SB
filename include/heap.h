
#ifndef HEAP_H
#define HEAP_H

#include "classe.h"
#include <vector>

class Heap {
private:
	static vector<ClasseInstancia*> objetos;

public:
	static void addObject(ClasseInstancia*);
};

#endif
