#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include "constantPool.h"

using namespace std;

struct attribute_info;

typedef struct 
{
	unsigned short constantvalue_index;
} constantvalue_attribute;

typedef struct 
{
	unsigned short start_pc;
	unsigned short end_pc;
	unsigned short handler_pc;
	unsigned short catch_type;
} t_exception_table;
	
typedef struct 
{
	unsigned short max_stack;
	unsigned short max_locals;
	unsigned int code_length;
	unsigned char* code;
	unsigned short exception_table_length;
	t_exception_table** exception_table;
	unsigned short attribute_count;
	attribute_info* attributes;
} code_attribute;

typedef struct 
{
	unsigned short number_of_exceptions;
	unsigned short* exception_index_table;
} exception_attribute;

typedef union 
{
	constantvalue_attribute constantvalue;
	code_attribute code;
	exception_attribute exception;
} t_info;

struct attribute_info 
{
	unsigned short name_index;
	unsigned int length;

	t_info* info;
};

t_exception_table* readExceptionHandler(FILE* fp);

t_info* readAttributeInfo(FILE* fp, cp_info *cp, unsigned short index, unsigned short length);

attribute_info readAttribute (FILE* fp, cp_info *cp);

attribute_info* readAttributes(FILE* fp, cp_info *cp, int length);

void printAttribute (attribute_info a, cp_info *cp);

void printAttributes(attribute_info* attributes, cp_info* cp, int length);

string getMnemonic(int opcode);

uint32_t getNBytesValue(uint8_t n, unsigned char* code, int* index);

void getOpcodeParams(unsigned char* code, int* index);

#endif
