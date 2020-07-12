#ifndef PRETTY_PRINTER_H
#define PRETTY_PRINTER_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 30

typedef enum DataType {
    STRING,
    INTEGER,
    FLOAT,
    DOUBLE
} DataType;

void printArray(void* dataArray, size_t arraySize, DataType type);
void printColumns(void* dataArray, size_t arraySize, DataType type, unsigned int numColumns);

#endif
