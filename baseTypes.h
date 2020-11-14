#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <math.h>
#include <sstream>
#include <vector>
#include <stdexcept>

using namespace std;

#define Float_NaN 0x7f800001
#define Float_PlusInfinity 0x7f800000
#define Float_MinusInfinity 0xff800000
#define Double_NaN 0x7ff0000000000001L 
#define Double_PlusInfinity 0x7ff0000000000000L
#define Double_MinusInfinity 0xfff0000000000000L

#define RT_BYTE 1
#define RT_BOOL 2
#define RT_CHAR 3
#define RT_SHORT 4
#define RT_INT 5
#define RT_FLOAT 6
#define RT_DOUBLE 7
#define RT_REFERENCE 8
#define RT_LONG 9

typedef uint8_t U1;
typedef uint16_t U2;
typedef uint32_t U4;

typedef union {
	U1 *array; //ponteiro para uma string
	U1 u1; //8 bytes
	U2 u2; //16 bytes
	U4 u4; //32 bytes
} ClassLoaderType;

typedef union element_u {
	double d;
	float f;
	uint32_t i;
	int32_t is;
	uint64_t l;
	int64_t ls;
	uint16_t s;
	int16_t ss;
	uint8_t b;
	int8_t bs;
	int* pi;
} element;

typedef struct {
	int* dims;
	int* array; 
} n_array;

typedef struct typedElement_s {
	element value;
	uint8_t type;
	uint8_t realType;
} typedElement;

U1 readU1 (FILE *fp);

U2 readU2 (FILE *fp);

U4 readU4 (FILE *fp);

U1 * readUTF8 (FILE* fp, int size);

string showUTF8 (unsigned char * s, int size);

float u4_to_float (ClassLoaderType in);

long u4_to_long (ClassLoaderType high, ClassLoaderType low);

double u4_to_double (ClassLoaderType high, ClassLoaderType low);

int checkFloat(float);

int checkDouble(double);

string float_to_string(float);

string double_to_string(double);

#endif