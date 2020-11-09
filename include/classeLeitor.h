#ifndef CLASSE_LEITOR_H
#define CLASSE_LEITOR_H

class Leitor;

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string>
#include "baseTypes.h"
#include "constantPool.h"
#include "classFlags.h"
#include "fields.h"
#include "attributes.h"
#include "interfaces.h"
#include "methods.h"
#include "methodArea.h"

#define MISSING_ARGUMENT 1
#define CANT_OPEN 2
#define INVALID_FILE 3
#define UNKNOWN_TYPE 4
#define INVALID_NAME 5
#define INVALID_EXTENSION 6
#define MISSING_MAIN 7

class Leitor {
public:
	Leitor(char *in);
	Leitor(std::string in);
	int run();
	int load();
	void printGeneralInformation();
	bool show();
	bool validExtension ();
	bool hasMain();
	method_info getMain();
	bool hasClinit();
	method_info getClinit();
	bool checkClass ();
	int getStatus();
	cp_info *getCP() const;
	U2 getLengthCP();
	char *getPath();
	method_info *getMethods();
	U2 getMethodsCount();
	U2 getThis_class();
	U2 getSuper_class();
	U2 getFieldsCount();
	field_info *getFields();
	field_info *getField(string field_name);
	method_info* getMethod(string name, string descriptor);
	Leitor* getClassThatHasSerachedMethod(string name, string descriptor);

private:
	bool findMain();
	bool findClinit();
	string getError(int);

	int status, mainMethod, clinit;
	bool foundMain, foundClinit;
	char *fileName;
	U2 minVersion, majVersion, lengthCP;
	U2 this_class, super_class, interfacesCount, fieldsCount;
	U2 methodsCount, accessFlags, attributesCount;
	U2 *interfaces;
	cp_info *constantPool;
	field_info *fields;
	method_info *methods;
	attribute_info *attributes;
	FILE *fp;
};

#endif