#include "pretty_printer.h"

// Static variables
static int i;

// Static function prototypes
static unsigned int getCharacterCountOfLongestElement();

void printColumns(void* dataArray, size_t arraySize, DataType type, unsigned int numColumns) {

    // Guard statement
    if(dataArray == NULL) {
        return;
    }

    switch(type) {

        case STRING:
            printf("string\n");
            break;
        
        case INTEGER:
            printf("integer\n");
            break;

        case FLOAT:
            printf("float\n");
            break;

        case DOUBLE:
            printf("double\n");
            break;

        default:
            printf("Cannot pretty-print invalid type as columns\n");
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

    char** stringIter = NULL;

    switch(type) {

        case STRING:
            for(i = 0; i < arraySize; ++i) {
                stringIter = (char**)dataArray;
                printf("%s\n", *stringIter);
                stringIter++;
            }
            break;
        
        case INTEGER:
            printf("integer\n");
            break;

        case FLOAT:
            printf("float\n");
            break;

        case DOUBLE:
            printf("double\n");
            break;

        default:
            printf("Cannot pretty-print invalid type as columns\n");
            return;
    }
}