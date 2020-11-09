#ifndef INTERFACES_H
#define INTERFACES_H

#include <iostream>
#include "constantPool.h"
#include "baseTypes.h"


unsigned short *readInterfaces (FILE *fp, int length);


void printInterfaces (unsigned short *interfaces, cp_info *cp, int length);


void printInterface (unsigned short interface, cp_info *cp);



void printInterface (unsigned short interface, cp_info *cp, int index);


#endif
