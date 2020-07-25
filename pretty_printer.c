#include "pretty_printer.h"

void printColumns(void* dataArray, size_t arraySize, DataType type, unsigned numColumns) {

    // Guard
    if(dataArray == NULL) {
        printf("[ERROR] cannot print null data array as columns\n");
        return;
    }

    if(numColumns > MAX_COLUMNS) {
        printf("[ERROR] cannot print data array as %d columns", numColumns);
        return;
    }

    // Assign default number of columns
    if(numColumns == 0) {
        numColumns = DEFAULT_COLUMNS;
    }

    switch(type) {

        case STRING:
            printStringArrayAsColumns((char**)dataArray, arraySize, numColumns);
            break;
        
        case INTEGER:
            printNumericArrayAsColumns((int*)dataArray, INTEGER, arraySize, numColumns);
            break;

        case FLOAT:
            printNumericArrayAsColumns((float*)dataArray, FLOAT, arraySize, numColumns);
            break;

        default:
            printf("[ERROR] Cannot pretty-print invalid type as columns\n");
            return;
    }
}

void printArray(void* dataArray, size_t arraySize, DataType type) {

    //Guard statements
    if(dataArray == NULL) {
        return;
    }

    if(arraySize == 0) {
        printf("empty array\n");
        return;
    }

    switch(type) {

        case STRING:
            printStringArray( (char**)dataArray, arraySize );
            break;
        
        case INTEGER:
            printIntegerArray( (int*)dataArray, arraySize );
            break;

        case FLOAT:
            printFloatArray( (float*)dataArray, arraySize, FLOAT_PRECISION );
            break;

        default:
            printf("[ERROR] cannot pretty-print invalid type as columns\n");
            return;
    }
}