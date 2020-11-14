#ifndef LOCALVARIABLES_H
#define LOCALVARIABLES_H

#include <cstdint>
#include <stack>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "baseTypes.h"


#define BITS (sizeof(int*) == 8)

#define INVALID 99
#define TYPE_NOT_SET 0
#define TYPE_INT 1
#define TYPE_FLOAT 2
#define TYPE_LONG 3
#define TYPE_DOUBLE 4
#define TYPE_BOOL 5
#define TYPE_REFERENCE 6


class LocalVariables 
{
private:
	//vetor de valor
	uint32_t *elements;
	//vetor tipos
	uint8_t *types;
	//maxima quantidade
	const uint16_t max;
	const uint16_t realMax;
	//diz se ocupa 2 espaços
	const bool dois;
public:
	
	LocalVariables(uint16_t);

	
	LocalVariables(uint16_t, bool);
	
	~LocalVariables();

	
	void printall() const;

	
	void set(int, typedElement);

	
	typedElement get(int) const;

	
	int getMax() const;

	
	const typedElement operator[] (const int) const;

};

#endif