#ifndef CLASSFLAGS_H
#define CLASSFLAGS_H

#include <iostream>
#include "baseTypes.h"

using namespace std;

const string flagNames[] = {"ACC_PUBLIC", "ACC_FINAL", "ACC_SUPER", "ACC_INTERFACE", "ACC_ABSTRACT"};
void showFlags (U2 flags);

#endif