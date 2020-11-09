#ifndef METHOD_AREA_H
#define METHOD_AREA_H

class MethodArea;

#include "classeLeitor.h"
#include "baseTypes.h"
#include "constantPool.h"
#include "frame.h"
#include "classe.h"
#include <map>
#include <algorithm>
#include <string.h>

using namespace std;

class MethodArea{
private:
	static map<string, ClasseEstatica*> classes;
	static FrameStack *fs;


public:
	static string path;
	static ClasseEstatica *getClass(string);
	static bool addClass(Leitor*);
    static bool addClass(string);
    static void setFrameStack(FrameStack*);
};

#endif