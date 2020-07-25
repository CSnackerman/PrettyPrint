#ifndef UTILITY_H
#define UTILITY_H

#include <time.h>

#include "pretty_printer.h"

// Test Utilities
void printTestHeader(const char* testName);

void incrementalStringArrayInit(char* stringArray[], const size_t size);
void incrementalIntArrayInit(int** intArray, const size_t size);
void incrementalFloatArrayInit(float** floatArray, const size_t size);

void randomStringArrayInit(char* stringArray[], const size_t size);

void cleanupStringArray(char* stringArray[], const size_t size);
void cleanupArray(void* array, const size_t size, DataType type);

int randRange(int lower, int upper);

// Pretty Print Utilities 
void printStringArray(char* stringArray[], const size_t size);
void printIntegerArray(int* intArray, const size_t size);
void printFloatArray(float* floatArray, const size_t size, const unsigned precision);

void printStringArrayAsColumns(char* stringArray[], const size_t size, unsigned columnCount);
void printNumericArrayAsColumns(void* dataArray, DataType type, const size_t size, unsigned columnCount);

int getColumnWidth(void* dataArray, const size_t size, DataType type);
int getLongestStringElementLength(char* stringArray[], const size_t size);
int getStringLengthOfLargestInt(int* intArray, const size_t size);
int getStringLengthOfLargestFloat(float* floatArray, const size_t size);

#endif