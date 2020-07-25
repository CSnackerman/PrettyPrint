#ifndef PRETTY_PRINTER_H
#define PRETTY_PRINTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "utility.h"

#define MAX_STRING_LENGTH 32
#define FLOAT_PRECISION 3
#define MAX_COLUMNS 5
#define DEFAULT_COLUMNS 5
#define COLUMN_SPACER 2
#define FILL_CHAR " "

void printArray(void* dataArray, size_t arraySize, DataType type);
void printColumns(void* dataArray, size_t arraySize, DataType type, unsigned numColumns);

#endif
