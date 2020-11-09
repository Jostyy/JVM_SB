#ifndef CONSTANTPOOL_H
#define CONSTANTPOOL_H

#include "baseTypes.h"

using namespace std;

typedef struct {
	U1 tag;
	ClassLoaderType *info;
} cp_info;

const string typeNames[] = {"UTF-8", "-", "Integer", "Float", "Long", "Double", "Class", "String", "Field", "Method", "Interface", "Name and Type"};

#define INVALID 99 
#define UTF8 1
#define INTEGER 3
#define FLOAT 4
#define LONG 5
#define DOUBLE 6
#define CLASS 7
#define STRING 8
#define FIELD_REF 9
#define METHOD_REF 10
#define INTERFACE_REF 11
#define NAME_AND_TYPE 12

int loadConstantPool (cp_info *constantPool, int tamanhoCP, FILE* fp);
string dereferenceIndex (cp_info *cp, U2 index);
void printConstantPool (cp_info *constantPool, int tamanhoCP);

#endif
