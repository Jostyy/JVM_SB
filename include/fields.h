
#ifndef FIELDS_H
#define FIELDS_H

#include "baseTypes.h"
#include "constantPool.h"
#include "attributes.h"

using namespace std;

typedef struct {
	unsigned char accessFlags;
	unsigned char name_index;
	unsigned char descriptor_index;
	unsigned char attributes_count;
	attribute_info *attributes;
} field_info;

string getFieldFlags(unsigned short flags);

void printField(field_info f, cp_info *cp, int index);

void printFields(field_info *f, cp_info *cp, int length);

field_info readField(FILE* fp, cp_info *cp);

field_info *readFields(FILE* fp, int length,cp_info *cp);

#endif
