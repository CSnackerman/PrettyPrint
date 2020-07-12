#include "pretty_printer.h"

// --- Utility Prototypes ---
static void printStringArray(char* stringArray[], size_t size);

// --- API ---

//TODO after normal printing of arrays of each data type
void printColumns(void* dataArray, size_t arraySize, DataType type, unsigned int numColumns) {

    // // Guard statement
    // if(dataArray == NULL) {
    //     return;
    // }

    // switch(type) {

    //     case STRING:
    //         printf("string\n");
    //         break;
        
    //     case INTEGER:
    //         printf("integer\n");
    //         break;

    //     case FLOAT:
    //         printf("float\n");
    //         break;

    //     case DOUBLE:
    //         printf("double\n");
    //         break;

    //     default:
    //         printf("Cannot pretty-print invalid type as columns\n");
    //         return;
    // }
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
            printf("integer\n");
            break;

        case FLOAT:
            printf("float\n");
            break;

        case DOUBLE:
            printf("double\n");
            break;

        default:
            printf("cannot pretty-print invalid type as columns\n");
            return;
    }
}

// --- Utility Definitions ---

static void printStringArray(char* stringArray[], size_t size) {

    int i;
    for(i = 0; i < size; ++i) {
        printf("%s\n", stringArray[i]);
    }

    printf("\n");

}